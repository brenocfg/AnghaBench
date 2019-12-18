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
typedef  int vm_fault_t ;
struct TYPE_2__ {unsigned long addr; } ;
struct pt_regs {unsigned long int_parm_long; int int_code; TYPE_1__ psw; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_NX ; 
 unsigned long PAGE_MASK ; 
 int VM_EXEC ; 
 int VM_FAULT_BADACCESS ; 
 int VM_WRITE ; 
 unsigned long __rewind_psw (TYPE_1__,int) ; 
 int do_exception (struct pt_regs*,int) ; 
 int /*<<< orphan*/  do_fault_error (struct pt_regs*,int,int) ; 
 int /*<<< orphan*/  do_low_address (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 

void do_protection_exception(struct pt_regs *regs)
{
	unsigned long trans_exc_code;
	int access;
	vm_fault_t fault;

	trans_exc_code = regs->int_parm_long;
	/*
	 * Protection exceptions are suppressing, decrement psw address.
	 * The exception to this rule are aborted transactions, for these
	 * the PSW already points to the correct location.
	 */
	if (!(regs->int_code & 0x200))
		regs->psw.addr = __rewind_psw(regs->psw, regs->int_code >> 16);
	/*
	 * Check for low-address protection.  This needs to be treated
	 * as a special case because the translation exception code
	 * field is not guaranteed to contain valid data in this case.
	 */
	if (unlikely(!(trans_exc_code & 4))) {
		do_low_address(regs);
		return;
	}
	if (unlikely(MACHINE_HAS_NX && (trans_exc_code & 0x80))) {
		regs->int_parm_long = (trans_exc_code & ~PAGE_MASK) |
					(regs->psw.addr & PAGE_MASK);
		access = VM_EXEC;
		fault = VM_FAULT_BADACCESS;
	} else {
		access = VM_WRITE;
		fault = do_exception(regs, access);
	}
	if (unlikely(fault))
		do_fault_error(regs, access, fault);
}