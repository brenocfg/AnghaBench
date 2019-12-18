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
struct task_struct {struct mm_struct* mm; } ;
struct pt_regs {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADRERR ; 
 int /*<<< orphan*/  SIGBUS ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  force_sig_info_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  no_context (struct pt_regs*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void
do_sigbus(struct pt_regs *regs, unsigned long error_code, unsigned long address)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->mm;

	up_read(&mm->mmap_sem);

	/* Kernel mode? Handle exceptions or die: */
	if (!user_mode(regs))
		no_context(regs, error_code, address);

	force_sig_info_fault(SIGBUS, BUS_ADRERR, address);
}