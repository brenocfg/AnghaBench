#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  long u64 ;
struct pt_regs {long cr_iip; scalar_t__ r9; int /*<<< orphan*/  r8; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;
struct TYPE_2__ {long ri; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 TYPE_1__* ia64_psr (struct pt_regs*) ; 

void
ia64_handle_exception (struct pt_regs *regs, const struct exception_table_entry *e)
{
	long fix = (u64) &e->fixup + e->fixup;

	regs->r8 = -EFAULT;
	if (fix & 4)
		regs->r9 = 0;
	regs->cr_iip = fix & ~0xf;
	ia64_psr(regs)->ri = fix & 0x3;		/* set continuation slot number */
}