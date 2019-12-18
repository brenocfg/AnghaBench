#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fpu; } ;
struct TYPE_4__ {int flags; TYPE_1__ thread; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  __cpu_invalidate_fpregs_state () ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  in_kernel_fpu ; 
 int /*<<< orphan*/  irq_fpu_usable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 

void kernel_fpu_begin(void)
{
	preempt_disable();

	WARN_ON_FPU(!irq_fpu_usable());
	WARN_ON_FPU(this_cpu_read(in_kernel_fpu));

	this_cpu_write(in_kernel_fpu, true);

	if (!(current->flags & PF_KTHREAD) &&
	    !test_thread_flag(TIF_NEED_FPU_LOAD)) {
		set_thread_flag(TIF_NEED_FPU_LOAD);
		/*
		 * Ignore return value -- we don't care if reg state
		 * is clobbered.
		 */
		copy_fpregs_to_fpstate(&current->thread.fpu);
	}
	__cpu_invalidate_fpregs_state();
}