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

/* Variables and functions */
 int IDECFG_WST_SHIFT ; 

__attribute__((used)) static int ep93xx_pata_get_wst(int pio_mode)
{
	int val;

	if (pio_mode == 0)
		val = 3;
	else if (pio_mode < 3)
		val = 2;
	else
		val = 1;

	return val << IDECFG_WST_SHIFT;
}