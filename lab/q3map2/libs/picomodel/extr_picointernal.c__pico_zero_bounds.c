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
typedef  int* picoVec3_t ;

/* Variables and functions */

void _pico_zero_bounds( picoVec3_t mins, picoVec3_t maxs ){
	int i;
	for ( i = 0; i < 3; i++ )
	{
		mins[i] = +999999;
		maxs[i] = -999999;
	}
}