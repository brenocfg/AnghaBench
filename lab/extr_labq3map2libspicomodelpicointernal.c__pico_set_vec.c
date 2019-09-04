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

void _pico_set_vec( picoVec3_t v, float a, float b, float c ){
	v[ 0 ] = a;
	v[ 1 ] = b;
	v[ 2 ] = c;
}