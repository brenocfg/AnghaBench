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
struct pt_regs {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_restart_syscall ; 
 int /*<<< orphan*/  compat_setup_restart_syscall (struct pt_regs*) ; 
 scalar_t__ is_compat_task () ; 

__attribute__((used)) static void setup_restart_syscall(struct pt_regs *regs)
{
	if (is_compat_task())
		compat_setup_restart_syscall(regs);
	else
		regs->regs[8] = __NR_restart_syscall;
}