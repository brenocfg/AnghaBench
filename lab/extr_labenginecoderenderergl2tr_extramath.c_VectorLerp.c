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

/* Variables and functions */

void VectorLerp( vec3_t a, vec3_t b, float lerp, vec3_t c)
{
	c[0] = a[0] * (1.0f - lerp) + b[0] * lerp;
	c[1] = a[1] * (1.0f - lerp) + b[1] * lerp;
	c[2] = a[2] * (1.0f - lerp) + b[2] * lerp;
}