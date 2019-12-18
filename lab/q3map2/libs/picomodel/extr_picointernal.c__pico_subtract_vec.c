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
typedef  scalar_t__* picoVec3_t ;

/* Variables and functions */

void _pico_subtract_vec( picoVec3_t a, picoVec3_t b, picoVec3_t dest ){
	dest[ 0 ] = a[ 0 ] - b[ 0 ];
	dest[ 1 ] = a[ 1 ] - b[ 1 ];
	dest[ 2 ] = a[ 2 ] - b[ 2 ];
}