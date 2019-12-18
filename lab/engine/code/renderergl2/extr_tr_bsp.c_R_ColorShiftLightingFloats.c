#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int integer; } ;
struct TYPE_3__ {int overbrightBits; } ;

/* Variables and functions */
 TYPE_2__* r_mapOverBrightBits ; 
 TYPE_1__ tr ; 

__attribute__((used)) static void R_ColorShiftLightingFloats(float in[4], float out[4])
{
	float	r, g, b;
	float   scale = (1 << (r_mapOverBrightBits->integer - tr.overbrightBits)) / 255.0f;

	r = in[0] * scale;
	g = in[1] * scale;
	b = in[2] * scale;

	// normalize by color instead of saturating to white
	if ( r > 1 || g > 1 || b > 1 ) {
		float	max;

		max = r > g ? r : g;
		max = max > b ? max : b;
		r = r / max;
		g = g / max;
		b = b / max;
	}

	out[0] = r;
	out[1] = g;
	out[2] = b;
	out[3] = in[3];
}