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
struct trapframe {int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_elr; int /*<<< orphan*/  tf_x; int /*<<< orphan*/  tf_lr; int /*<<< orphan*/  tf_sp; } ;
struct thread {int /*<<< orphan*/  td_proc; struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/ * x; int /*<<< orphan*/  spsr; int /*<<< orphan*/  elr; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
fill_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *frame;

	frame = td->td_frame;
	regs->sp = frame->tf_sp;
	regs->lr = frame->tf_lr;
	regs->elr = frame->tf_elr;
	regs->spsr = frame->tf_spsr;

	memcpy(regs->x, frame->tf_x, sizeof(regs->x));

#ifdef COMPAT_FREEBSD32
	/*
	 * We may be called here for a 32bits process, if we're using a
	 * 64bits debugger. If so, put PC and SPSR where it expects it.
	 */
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		regs->x[15] = frame->tf_elr;
		regs->x[16] = frame->tf_spsr;
	}
#endif
	return (0);
}