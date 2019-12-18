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
 int /*<<< orphan*/  CONSOLE_FLUSH_PENDING ; 
 int /*<<< orphan*/  KMSG_DUMP_PANIC ; 
 int /*<<< orphan*/  bust_spinlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_flush_on_panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  kmsg_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_safe_flush_on_panic () ; 

extern void panic_flush_kmsg_end(void)
{
	printk_safe_flush_on_panic();
	kmsg_dump(KMSG_DUMP_PANIC);
	bust_spinlocks(0);
	debug_locks_off();
	console_flush_on_panic(CONSOLE_FLUSH_PENDING);
}