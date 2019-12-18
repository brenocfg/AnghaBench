#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {TYPE_1__* td_frame; int /*<<< orphan*/  td_proc; } ;
struct TYPE_5__ {uintptr_t ss_size; scalar_t__ ss_sp; } ;
typedef  TYPE_2__ stack_t ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {uintptr_t tf_rsp; uintptr_t tf_rip; int tf_rdi; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; void* tf_es; void* tf_ds; scalar_t__ tf_rbp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 void* _udatasel ; 
 int /*<<< orphan*/  _ufssel ; 
 int /*<<< orphan*/  _ugssel ; 
 int /*<<< orphan*/  cpu_thread_clean (struct thread*) ; 
 int /*<<< orphan*/  suword (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suword32 (void*,int /*<<< orphan*/ ) ; 

void
cpu_set_upcall(struct thread *td, void (*entry)(void *), void *arg,
    stack_t *stack)
{

	/* 
	 * Do any extra cleaning that needs to be done.
	 * The thread may have optional components
	 * that are not present in a fresh thread.
	 * This may be a recycled thread so make it look
	 * as though it's newly allocated.
	 */
	cpu_thread_clean(td);

#ifdef COMPAT_FREEBSD32
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		/*
		 * Set the trap frame to point at the beginning of the entry
		 * function.
		 */
		td->td_frame->tf_rbp = 0;
		td->td_frame->tf_rsp =
		   (((uintptr_t)stack->ss_sp + stack->ss_size - 4) & ~0x0f) - 4;
		td->td_frame->tf_rip = (uintptr_t)entry;

		/* Return address sentinel value to stop stack unwinding. */
		suword32((void *)td->td_frame->tf_rsp, 0);

		/* Pass the argument to the entry point. */
		suword32((void *)(td->td_frame->tf_rsp + sizeof(int32_t)),
		    (uint32_t)(uintptr_t)arg);

		return;
	}
#endif

	/*
	 * Set the trap frame to point at the beginning of the uts
	 * function.
	 */
	td->td_frame->tf_rbp = 0;
	td->td_frame->tf_rsp =
	    ((register_t)stack->ss_sp + stack->ss_size) & ~0x0f;
	td->td_frame->tf_rsp -= 8;
	td->td_frame->tf_rip = (register_t)entry;
	td->td_frame->tf_ds = _udatasel;
	td->td_frame->tf_es = _udatasel;
	td->td_frame->tf_fs = _ufssel;
	td->td_frame->tf_gs = _ugssel;
	td->td_frame->tf_flags = TF_HASSEGS;

	/* Return address sentinel value to stop stack unwinding. */
	suword((void *)td->td_frame->tf_rsp, 0);

	/* Pass the argument to the entry point. */
	td->td_frame->tf_rdi = (register_t)arg;
}