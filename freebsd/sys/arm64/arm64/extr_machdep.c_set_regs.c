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
struct trapframe {int tf_elr; int tf_spsr; int /*<<< orphan*/  tf_x; int /*<<< orphan*/  tf_lr; int /*<<< orphan*/  tf_sp; } ;
struct thread {int /*<<< orphan*/  td_proc; struct trapframe* td_frame; } ;
struct reg {int elr; int spsr; int* x; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; } ;

/* Variables and functions */
 int PSR_FLAGS ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

int
set_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *frame;

	frame = td->td_frame;
	frame->tf_sp = regs->sp;
	frame->tf_lr = regs->lr;
	frame->tf_elr = regs->elr;
	frame->tf_spsr &= ~PSR_FLAGS;
	frame->tf_spsr |= regs->spsr & PSR_FLAGS;

	memcpy(frame->tf_x, regs->x, sizeof(frame->tf_x));

#ifdef COMPAT_FREEBSD32
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		/*
		 * We may be called for a 32bits process if we're using
		 * a 64bits debugger. If so, get PC and SPSR from where
		 * it put it.
		 */
		frame->tf_elr = regs->x[15];
		frame->tf_spsr = regs->x[16] & PSR_FLAGS;
	}
#endif
	return (0);
}