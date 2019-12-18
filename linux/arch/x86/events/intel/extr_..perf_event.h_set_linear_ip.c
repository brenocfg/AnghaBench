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
struct pt_regs {int flags; unsigned long ip; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int PERF_EFLAGS_VM ; 
 int X86_VM_MASK ; 
 int /*<<< orphan*/  __KERNEL_CS ; 
 int /*<<< orphan*/  __USER_CS ; 
 scalar_t__ kernel_ip (unsigned long) ; 

__attribute__((used)) static inline void set_linear_ip(struct pt_regs *regs, unsigned long ip)
{
	regs->cs = kernel_ip(ip) ? __KERNEL_CS : __USER_CS;
	if (regs->flags & X86_VM_MASK)
		regs->flags ^= (PERF_EFLAGS_VM | X86_VM_MASK);
	regs->ip = ip;
}