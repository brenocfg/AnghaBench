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
struct thread {int /*<<< orphan*/  td_pcb; } ;
struct stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_FP (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_IS_SWAPPED (struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stack_capture (struct thread*,struct stack*,int /*<<< orphan*/ ) ; 

void
stack_save_td(struct stack *st, struct thread *td)
{

	if (TD_IS_SWAPPED(td))
		panic("stack_save_td: swapped");
	if (TD_IS_RUNNING(td))
		panic("stack_save_td: running");

	stack_capture(td, st, PCB_FP(td->td_pcb));
}