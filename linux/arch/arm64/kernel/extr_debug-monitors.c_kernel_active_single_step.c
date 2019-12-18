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
 int DBG_MDSCR_SS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int mdscr_read () ; 

int kernel_active_single_step(void)
{
	WARN_ON(!irqs_disabled());
	return mdscr_read() & DBG_MDSCR_SS;
}