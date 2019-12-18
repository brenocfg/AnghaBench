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
typedef  int /*<<< orphan*/  u_register_t ;
struct thread {TYPE_2__* td_pcb; } ;
struct stack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sp; int /*<<< orphan*/  pc; } ;
struct TYPE_4__ {TYPE_1__ pcb_regs; } ;

/* Variables and functions */
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_IS_SWAPPED (struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stack_capture (struct stack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
stack_save_td(struct stack *st, struct thread *td)
{
	u_register_t pc, sp;

	if (TD_IS_SWAPPED(td))
		panic("stack_save_td: swapped");
	if (TD_IS_RUNNING(td))
		panic("stack_save_td: running");

	pc = td->td_pcb->pcb_regs.pc;
	sp = td->td_pcb->pcb_regs.sp;
	stack_capture(st, pc, sp);
}