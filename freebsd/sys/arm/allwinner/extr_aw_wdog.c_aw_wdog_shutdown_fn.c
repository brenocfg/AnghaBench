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
 int RB_HALT ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  aw_wdog_watchdog_reset () ; 

__attribute__((used)) static void
aw_wdog_shutdown_fn(void *private, int howto)
{
	if ((howto & (RB_POWEROFF|RB_HALT)) == 0)
		aw_wdog_watchdog_reset();
}