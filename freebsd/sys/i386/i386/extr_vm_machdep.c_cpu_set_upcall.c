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
struct thread {TYPE_1__* td_frame; } ;
struct TYPE_5__ {int ss_size; scalar_t__ ss_sp; } ;
typedef  TYPE_2__ stack_t ;
struct TYPE_4__ {int tf_esp; int tf_eip; scalar_t__ tf_ebp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_thread_clean (struct thread*) ; 
 int /*<<< orphan*/  suword (void*,int) ; 

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

	/*
	 * Set the trap frame to point at the beginning of the entry
	 * function.
	 */
	td->td_frame->tf_ebp = 0; 
	td->td_frame->tf_esp =
	    (((int)stack->ss_sp + stack->ss_size - 4) & ~0x0f) - 4;
	td->td_frame->tf_eip = (int)entry;

	/* Return address sentinel value to stop stack unwinding. */
	suword((void *)td->td_frame->tf_esp, 0);

	/* Pass the argument to the entry point. */
	suword((void *)(td->td_frame->tf_esp + sizeof(void *)),
	    (int)arg);
}