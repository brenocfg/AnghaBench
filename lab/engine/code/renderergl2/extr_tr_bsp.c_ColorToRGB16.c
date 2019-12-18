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
typedef  float uint16_t ;

/* Variables and functions */

void ColorToRGB16(const vec3_t color, uint16_t rgb16[3])
{
	rgb16[0] = color[0] * 65535.0f + 0.5f;
	rgb16[1] = color[1] * 65535.0f + 0.5f;
	rgb16[2] = color[2] * 65535.0f + 0.5f;
}