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
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_monitor_init () ; 
 int /*<<< orphan*/  oslar_el1 ; 

void
dbg_init(void)
{

	/* Clear OS lock */
	WRITE_SPECIALREG(oslar_el1, 0);

	/* This permits DDB to use debug registers for watchpoints. */
	dbg_monitor_init();

	/* TODO: Eventually will need to initialize debug registers here. */
}