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
struct pt_regs {unsigned long* iaoq; int iir; scalar_t__* gr; } ;
struct exception_table_entry {int fixup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EFAULT ; 
 scalar_t__ PSW_B ; 
 scalar_t__ VM_READ ; 
 scalar_t__ parisc_acctyp (int /*<<< orphan*/ ,int) ; 
 struct exception_table_entry* search_exception_tables (unsigned long) ; 

int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fix;

	fix = search_exception_tables(regs->iaoq[0]);
	if (fix) {
		/*
		 * Fix up get_user() and put_user().
		 * ASM_EXCEPTIONTABLE_ENTRY_EFAULT() sets the least-significant
		 * bit in the relative address of the fixup routine to indicate
		 * that %r8 should be loaded with -EFAULT to report a userspace
		 * access error.
		 */
		if (fix->fixup & 1) {
			regs->gr[8] = -EFAULT;

			/* zero target register for get_user() */
			if (parisc_acctyp(0, regs->iir) == VM_READ) {
				int treg = regs->iir & 0x1f;
				BUG_ON(treg == 0);
				regs->gr[treg] = 0;
			}
		}

		regs->iaoq[0] = (unsigned long)&fix->fixup + fix->fixup;
		regs->iaoq[0] &= ~3;
		/*
		 * NOTE: In some cases the faulting instruction
		 * may be in the delay slot of a branch. We
		 * don't want to take the branch, so we don't
		 * increment iaoq[1], instead we set it to be
		 * iaoq[0]+4, and clear the B bit in the PSW
		 */
		regs->iaoq[1] = regs->iaoq[0] + 4;
		regs->gr[0] &= ~PSW_B; /* IPSW in gr[0] */

		return 1;
	}

	return 0;
}