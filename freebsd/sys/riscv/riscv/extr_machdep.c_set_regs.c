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
struct trapframe {int /*<<< orphan*/  tf_a; int /*<<< orphan*/  tf_s; int /*<<< orphan*/  tf_t; int /*<<< orphan*/  tf_tp; int /*<<< orphan*/  tf_gp; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/  tf_ra; int /*<<< orphan*/  tf_sepc; } ;
struct thread {struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/  a; int /*<<< orphan*/  s; int /*<<< orphan*/  t; int /*<<< orphan*/  tp; int /*<<< orphan*/  gp; int /*<<< orphan*/  sp; int /*<<< orphan*/  ra; int /*<<< orphan*/  sepc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
set_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *frame;

	frame = td->td_frame;
	frame->tf_sepc = regs->sepc;
	frame->tf_ra = regs->ra;
	frame->tf_sp = regs->sp;
	frame->tf_gp = regs->gp;
	frame->tf_tp = regs->tp;

	memcpy(frame->tf_t, regs->t, sizeof(frame->tf_t));
	memcpy(frame->tf_s, regs->s, sizeof(frame->tf_s));
	memcpy(frame->tf_a, regs->a, sizeof(frame->tf_a));

	return (0);
}