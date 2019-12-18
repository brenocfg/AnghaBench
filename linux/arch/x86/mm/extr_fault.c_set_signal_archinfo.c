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
struct TYPE_2__ {unsigned long error_code; unsigned long cr2; int /*<<< orphan*/  trap_nr; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned long TASK_SIZE_MAX ; 
 unsigned long X86_PF_PROT ; 
 unsigned long X86_PF_USER ; 
 int /*<<< orphan*/  X86_TRAP_PF ; 
 struct task_struct* current ; 

__attribute__((used)) static void set_signal_archinfo(unsigned long address,
				unsigned long error_code)
{
	struct task_struct *tsk = current;

	/*
	 * To avoid leaking information about the kernel page
	 * table layout, pretend that user-mode accesses to
	 * kernel addresses are always protection faults.
	 *
	 * NB: This means that failed vsyscalls with vsyscall=none
	 * will have the PROT bit.  This doesn't leak any
	 * information and does not appear to cause any problems.
	 */
	if (address >= TASK_SIZE_MAX)
		error_code |= X86_PF_PROT;

	tsk->thread.trap_nr = X86_TRAP_PF;
	tsk->thread.error_code = error_code | X86_PF_USER;
	tsk->thread.cr2 = address;
}