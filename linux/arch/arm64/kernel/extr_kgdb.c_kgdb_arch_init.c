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
 int /*<<< orphan*/  kgdb_brkpt_hook ; 
 int /*<<< orphan*/  kgdb_compiled_brkpt_hook ; 
 int /*<<< orphan*/  kgdb_notifier ; 
 int /*<<< orphan*/  kgdb_step_hook ; 
 int register_die_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_kernel_break_hook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_kernel_step_hook (int /*<<< orphan*/ *) ; 

int kgdb_arch_init(void)
{
	int ret = register_die_notifier(&kgdb_notifier);

	if (ret != 0)
		return ret;

	register_kernel_break_hook(&kgdb_brkpt_hook);
	register_kernel_break_hook(&kgdb_compiled_brkpt_hook);
	register_kernel_step_hook(&kgdb_step_hook);
	return 0;
}