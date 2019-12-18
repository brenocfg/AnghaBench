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
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 

extern void panic_flush_kmsg_start(void)
{
	/*
	 * These are mostly taken from kernel/panic.c, but tries to do
	 * relatively minimal work. Don't use delay functions (TB may
	 * be broken), don't crash dump (need to set a firmware log),
	 * don't run notifiers. We do want to get some information to
	 * Linux console.
	 */
	console_verbose();
	bust_spinlocks(1);
}