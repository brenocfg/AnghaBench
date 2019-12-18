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
typedef  float* picoVec3_t ;

/* Variables and functions */

void _pico_expand_bounds( picoVec3_t p, picoVec3_t mins, picoVec3_t maxs ){
	int i;
	for ( i = 0; i < 3; i++ )
	{
		float value = p[i];
		if ( value < mins[i] ) {
			mins[i] = value;
		}
		if ( value > maxs[i] ) {
			maxs[i] = value;
		}
	}
}