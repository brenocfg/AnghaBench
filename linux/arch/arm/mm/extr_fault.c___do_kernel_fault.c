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
struct pt_regs {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ALERT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fixup_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 int /*<<< orphan*/  show_pte (int /*<<< orphan*/ ,struct mm_struct*,unsigned long) ; 

__attribute__((used)) static void
__do_kernel_fault(struct mm_struct *mm, unsigned long addr, unsigned int fsr,
		  struct pt_regs *regs)
{
	/*
	 * Are we prepared to handle this kernel fault?
	 */
	if (fixup_exception(regs))
		return;

	/*
	 * No handler, we'll have to terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);
	pr_alert("8<--- cut here ---\n");
	pr_alert("Unable to handle kernel %s at virtual address %08lx\n",
		 (addr < PAGE_SIZE) ? "NULL pointer dereference" :
		 "paging request", addr);

	show_pte(KERN_ALERT, mm, addr);
	die("Oops", regs, fsr);
	bust_spinlocks(0);
	do_exit(SIGKILL);
}