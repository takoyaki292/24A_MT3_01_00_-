#include <Novice.h>
#include <math.h>
#include <stdio.h>
const char kWindowTitle[] = "GC2B_08_シミズ_タクミ";

struct Matrix4x4
{
	float m[4][4];
};

float cot(float a)
{
	return cosf(a) / sinf(a);
}
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 m = {};
	float a = 1 / aspectRatio;
	m.m[0][0] = a*cot(fovY/2);
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;

	m.m[1][0] = 0;
	m.m[1][1] = cot(fovY/2);
	m.m[1][2] = 0;
	m.m[1][3] = 0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = farClip/(farClip-nearClip);
	m.m[2][3] = 1;

	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = -nearClip*farClip/(farClip-nearClip);
	m.m[3][3] = 0;
	return m;
}
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float nearClip,float farClip)
{
	Matrix4x4 m = {};
	m.m[0][0] = 2.0f/ (right - left);
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] =0;

	m.m[1][0] = 0;
	m.m[1][1] = 2.0f /(top-bottom);
	m.m[1][2] = 0;
	m.m[1][3] =0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 2.0f/(farClip-nearClip);
	m.m[2][3] = 0;

	m.m[3][0] = (left + right) / (left - right);
	m.m[3][1] = -(top + bottom) / -(bottom - top);
	m.m[3][2] = nearClip/(nearClip-farClip);
	m.m[3][3] = 1;

	return m;
 }
//ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 m = {};
	m.m[0][0] = width / 2.0f;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;

	m.m[1][0] = 0;
	m.m[1][1] = -height /2.0f;
	m.m[1][2] = 0;
	m.m[1][3] = 0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = maxDepth-minDepth;
	m.m[2][3] = 0;

	m.m[3][0] = left+(width /2.0f);
	m.m[3][1] = top+ (height /2.0f);
	m.m[3][2] = minDepth;
	m.m[3][3] = 1;

	return m;
}
//printfの関数
static const int kRowHeight = 20;
static const int kColmnWidht = 100;
void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColmnWidht, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
	printf("\n");
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Matrix4x4 orthographicMatrix = 
		MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Matrix4x4 perspectiveFovMatrix =
		MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix4x4 viewportMatrix =
		MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, orthographicMatrix);
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix);
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
