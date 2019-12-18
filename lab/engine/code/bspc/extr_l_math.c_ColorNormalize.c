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
typedef  float vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 

vec_t ColorNormalize (vec3_t in, vec3_t out)
{
	float	max, scale;

	max = in[0];
	if (in[1] > max)
		max = in[1];
	if (in[2] > max)
		max = in[2];

	if (max == 0)
		return 0;

	scale = 1.0 / max;

	VectorScale (in, scale, out);

	return max;
}