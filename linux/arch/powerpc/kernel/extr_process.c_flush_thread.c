#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_ptrace_hw_breakpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  set_debug_reg_defaults (int /*<<< orphan*/ *) ; 

void flush_thread(void)
{
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	flush_ptrace_hw_breakpoint(current);
#else /* CONFIG_HAVE_HW_BREAKPOINT */
	set_debug_reg_defaults(&current->thread);
#endif /* CONFIG_HAVE_HW_BREAKPOINT */
}