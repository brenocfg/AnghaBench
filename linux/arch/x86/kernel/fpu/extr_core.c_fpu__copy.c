#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  xsave; } ;
struct fpu {int last_cpu; TYPE_3__ state; } ;
struct TYPE_7__ {struct fpu fpu; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_8__ {struct fpu fpu; } ;
struct TYPE_10__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (struct fpu*) ; 
 int /*<<< orphan*/  copy_kernel_to_fpregs (TYPE_3__*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  fpregs_lock () ; 
 int /*<<< orphan*/  fpregs_unlock () ; 
 int /*<<< orphan*/  fpu_kernel_xstate_size ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_x86_fpu_copy_dst (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_copy_src (struct fpu*) ; 

int fpu__copy(struct task_struct *dst, struct task_struct *src)
{
	struct fpu *dst_fpu = &dst->thread.fpu;
	struct fpu *src_fpu = &src->thread.fpu;

	dst_fpu->last_cpu = -1;

	if (!static_cpu_has(X86_FEATURE_FPU))
		return 0;

	WARN_ON_FPU(src_fpu != &current->thread.fpu);

	/*
	 * Don't let 'init optimized' areas of the XSAVE area
	 * leak into the child task:
	 */
	memset(&dst_fpu->state.xsave, 0, fpu_kernel_xstate_size);

	/*
	 * If the FPU registers are not current just memcpy() the state.
	 * Otherwise save current FPU registers directly into the child's FPU
	 * context, without any memory-to-memory copying.
	 *
	 * ( The function 'fails' in the FNSAVE case, which destroys
	 *   register contents so we have to load them back. )
	 */
	fpregs_lock();
	if (test_thread_flag(TIF_NEED_FPU_LOAD))
		memcpy(&dst_fpu->state, &src_fpu->state, fpu_kernel_xstate_size);

	else if (!copy_fpregs_to_fpstate(dst_fpu))
		copy_kernel_to_fpregs(&dst_fpu->state);

	fpregs_unlock();

	set_tsk_thread_flag(dst, TIF_NEED_FPU_LOAD);

	trace_x86_fpu_copy_src(src_fpu);
	trace_x86_fpu_copy_dst(dst_fpu);

	return 0;
}