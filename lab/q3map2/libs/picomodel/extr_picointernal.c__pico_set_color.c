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
typedef  int* picoColor_t ;

/* Variables and functions */

void _pico_set_color( picoColor_t c, int r, int g, int b, int a ){
	c[ 0 ] = r;
	c[ 1 ] = g;
	c[ 2 ] = b;
	c[ 3 ] = a;
}