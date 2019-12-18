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
typedef  scalar_t__ u32 ;
struct pt_regs {int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  orig_ax; int /*<<< orphan*/  r10; int /*<<< orphan*/  di; } ;

/* Variables and functions */
 scalar_t__ AUDIT_ARCH_X86_64 ; 
 int /*<<< orphan*/  audit_syscall_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_audit_syscall_entry(struct pt_regs *regs, u32 arch)
{
#ifdef CONFIG_X86_64
	if (arch == AUDIT_ARCH_X86_64) {
		audit_syscall_entry(regs->orig_ax, regs->di,
				    regs->si, regs->dx, regs->r10);
	} else
#endif
	{
		audit_syscall_entry(regs->orig_ax, regs->bx,
				    regs->cx, regs->dx, regs->si);
	}
}