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
struct pt_regs {int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  ax; int /*<<< orphan*/  sp; int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  printk_ratelimited (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_unhandled_signals ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

__attribute__((used)) static void warn_bad_vsyscall(const char *level, struct pt_regs *regs,
			      const char *message)
{
	if (!show_unhandled_signals)
		return;

	printk_ratelimited("%s%s[%d] %s ip:%lx cs:%lx sp:%lx ax:%lx si:%lx di:%lx\n",
			   level, current->comm, task_pid_nr(current),
			   message, regs->ip, regs->cs,
			   regs->sp, regs->ax, regs->si, regs->di);
}