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
typedef  int* mat4_t ;

/* Variables and functions */

void Mat4Multiply( const mat4_t in1, const mat4_t in2, mat4_t out )
{
	out[ 0] = in1[ 0] * in2[ 0] + in1[ 4] * in2[ 1] + in1[ 8] * in2[ 2] + in1[12] * in2[ 3];
	out[ 1] = in1[ 1] * in2[ 0] + in1[ 5] * in2[ 1] + in1[ 9] * in2[ 2] + in1[13] * in2[ 3];
	out[ 2] = in1[ 2] * in2[ 0] + in1[ 6] * in2[ 1] + in1[10] * in2[ 2] + in1[14] * in2[ 3];
	out[ 3] = in1[ 3] * in2[ 0] + in1[ 7] * in2[ 1] + in1[11] * in2[ 2] + in1[15] * in2[ 3];

	out[ 4] = in1[ 0] * in2[ 4] + in1[ 4] * in2[ 5] + in1[ 8] * in2[ 6] + in1[12] * in2[ 7];
	out[ 5] = in1[ 1] * in2[ 4] + in1[ 5] * in2[ 5] + in1[ 9] * in2[ 6] + in1[13] * in2[ 7];
	out[ 6] = in1[ 2] * in2[ 4] + in1[ 6] * in2[ 5] + in1[10] * in2[ 6] + in1[14] * in2[ 7];
	out[ 7] = in1[ 3] * in2[ 4] + in1[ 7] * in2[ 5] + in1[11] * in2[ 6] + in1[15] * in2[ 7];

	out[ 8] = in1[ 0] * in2[ 8] + in1[ 4] * in2[ 9] + in1[ 8] * in2[10] + in1[12] * in2[11];
	out[ 9] = in1[ 1] * in2[ 8] + in1[ 5] * in2[ 9] + in1[ 9] * in2[10] + in1[13] * in2[11];
	out[10] = in1[ 2] * in2[ 8] + in1[ 6] * in2[ 9] + in1[10] * in2[10] + in1[14] * in2[11];
	out[11] = in1[ 3] * in2[ 8] + in1[ 7] * in2[ 9] + in1[11] * in2[10] + in1[15] * in2[11];

	out[12] = in1[ 0] * in2[12] + in1[ 4] * in2[13] + in1[ 8] * in2[14] + in1[12] * in2[15];
	out[13] = in1[ 1] * in2[12] + in1[ 5] * in2[13] + in1[ 9] * in2[14] + in1[13] * in2[15];
	out[14] = in1[ 2] * in2[12] + in1[ 6] * in2[13] + in1[10] * in2[14] + in1[14] * in2[15];
	out[15] = in1[ 3] * in2[12] + in1[ 7] * in2[13] + in1[11] * in2[14] + in1[15] * in2[15];
}