#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  personality; TYPE_2__* mm; } ;
struct TYPE_9__ {int orig_ax; } ;
struct TYPE_7__ {int /*<<< orphan*/  ia32_compat; } ;
struct TYPE_8__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_IMPLIES_EXEC ; 
 int /*<<< orphan*/  TIF_IA32 ; 
 int /*<<< orphan*/  TIF_X32 ; 
 int /*<<< orphan*/  TS_COMPAT ; 
 int __NR_x32_execve ; 
 int __X32_SYSCALL_BIT ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 TYPE_5__* current_thread_info () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_3__* task_pt_regs (TYPE_4__*) ; 

__attribute__((used)) static void __set_personality_x32(void)
{
#ifdef CONFIG_X86_X32
	clear_thread_flag(TIF_IA32);
	set_thread_flag(TIF_X32);
	if (current->mm)
		current->mm->context.ia32_compat = TIF_X32;
	current->personality &= ~READ_IMPLIES_EXEC;
	/*
	 * in_32bit_syscall() uses the presence of the x32 syscall bit
	 * flag to determine compat status.  The x86 mmap() code relies on
	 * the syscall bitness so set x32 syscall bit right here to make
	 * in_32bit_syscall() work during exec().
	 *
	 * Pretend to come from a x32 execve.
	 */
	task_pt_regs(current)->orig_ax = __NR_x32_execve | __X32_SYSCALL_BIT;
	current_thread_info()->status &= ~TS_COMPAT;
#endif
}