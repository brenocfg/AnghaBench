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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct thread {TYPE_1__* td_pcb; } ;
struct stack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_sp; } ;

/* Variables and functions */
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_IS_SWAPPED (struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stack_capture (struct stack*,int /*<<< orphan*/ ) ; 

void
stack_save_td(struct stack *st, struct thread *td)
{
	vm_offset_t frame;

	if (TD_IS_SWAPPED(td))
		panic("stack_save_td: swapped");
	if (TD_IS_RUNNING(td))
		panic("stack_save_td: running");

	frame = td->td_pcb->pcb_sp;
	stack_capture(st, frame);
}