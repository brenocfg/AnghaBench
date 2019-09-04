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
typedef  float* vec2_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorSet (float*,float,float,float) ; 

void R_CalcTexDirs(vec3_t sdir, vec3_t tdir, const vec3_t v1, const vec3_t v2,
				   const vec3_t v3, const vec2_t w1, const vec2_t w2, const vec2_t w3)
{
	float			x1, x2, y1, y2, z1, z2;
	float			s1, s2, t1, t2, r;

	x1 = v2[0] - v1[0];
	x2 = v3[0] - v1[0];
	y1 = v2[1] - v1[1];
	y2 = v3[1] - v1[1];
	z1 = v2[2] - v1[2];
	z2 = v3[2] - v1[2];

	s1 = w2[0] - w1[0];
	s2 = w3[0] - w1[0];
	t1 = w2[1] - w1[1];
	t2 = w3[1] - w1[1];

	r = s1 * t2 - s2 * t1;
	if (r) r = 1.0f / r;

	VectorSet(sdir, (t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
	VectorSet(tdir, (s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);
}