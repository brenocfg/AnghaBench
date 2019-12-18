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
struct trapframe {int tf_spsr; } ;
struct TYPE_2__ {scalar_t__ md_spinlock_count; } ;
struct thread {TYPE_1__ td_md; scalar_t__ td_pticks; struct trapframe* td_frame; } ;

/* Variables and functions */
 int PSR_F ; 
 int PSR_I ; 
 scalar_t__ __predict_true (int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  enable_interrupts (int) ; 
 int /*<<< orphan*/  syscall (struct thread*,struct trapframe*) ; 

void
swi_handler(struct trapframe *frame)
{
	struct thread *td = curthread;

	td->td_frame = frame;

	td->td_pticks = 0;

	/*
	 * Enable interrupts if they were enabled before the exception.
	 * Since all syscalls *should* come from user mode it will always
	 * be safe to enable them, but check anyway.
	 */
	if (td->td_md.md_spinlock_count == 0) {
		if (__predict_true(frame->tf_spsr & PSR_I) == 0)
			enable_interrupts(PSR_I);
		if (__predict_true(frame->tf_spsr & PSR_F) == 0)
			enable_interrupts(PSR_F);
	}

	syscall(td, frame);
}