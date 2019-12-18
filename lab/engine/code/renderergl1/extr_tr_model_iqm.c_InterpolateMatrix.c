#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void InterpolateMatrix( float *a, float *b, float lerp, float *mat ) {
	float unLerp = 1.0f - lerp;

	mat[ 0] = a[ 0] * unLerp + b[ 0] * lerp;
	mat[ 1] = a[ 1] * unLerp + b[ 1] * lerp;
	mat[ 2] = a[ 2] * unLerp + b[ 2] * lerp;
	mat[ 3] = a[ 3] * unLerp + b[ 3] * lerp;
	mat[ 4] = a[ 4] * unLerp + b[ 4] * lerp;
	mat[ 5] = a[ 5] * unLerp + b[ 5] * lerp;
	mat[ 6] = a[ 6] * unLerp + b[ 6] * lerp;
	mat[ 7] = a[ 7] * unLerp + b[ 7] * lerp;
	mat[ 8] = a[ 8] * unLerp + b[ 8] * lerp;
	mat[ 9] = a[ 9] * unLerp + b[ 9] * lerp;
	mat[10] = a[10] * unLerp + b[10] * lerp;
	mat[11] = a[11] * unLerp + b[11] * lerp;
}