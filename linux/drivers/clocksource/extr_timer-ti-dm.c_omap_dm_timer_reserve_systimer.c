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
 int ENODEV ; 
 scalar_t__ omap_dm_timer_reserved_systimer (int) ; 
 int omap_reserved_systimers ; 

int omap_dm_timer_reserve_systimer(int id)
{
	if (omap_dm_timer_reserved_systimer(id))
		return -ENODEV;

	omap_reserved_systimers |= (1 << (id - 1));

	return 0;
}