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
typedef  float* vec3_t ;
typedef  float* mat4_t ;

/* Variables and functions */

void Mat4Translation( vec3_t vec, mat4_t out )
{
	out[ 0] = 1.0f; out[ 4] = 0.0f; out[ 8] = 0.0f; out[12] = vec[0];
	out[ 1] = 0.0f; out[ 5] = 1.0f; out[ 9] = 0.0f; out[13] = vec[1];
	out[ 2] = 0.0f; out[ 6] = 0.0f; out[10] = 1.0f; out[14] = vec[2];
	out[ 3] = 0.0f; out[ 7] = 0.0f; out[11] = 0.0f; out[15] = 1.0f;
}