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
typedef  int /*<<< orphan*/ * picoVec2_t ;

/* Variables and functions */

void _pico_copy_vec2( picoVec2_t src, picoVec2_t dest ){
	dest[ 0 ] = src[ 0 ];
	dest[ 1 ] = src[ 1 ];
}