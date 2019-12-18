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
struct thread {TYPE_1__* td_pcb; scalar_t__ td_frame; } ;
struct TYPE_2__ {uintptr_t* pcb_x; uintptr_t pcb_sp; int /*<<< orphan*/  pcb_vfpcpu; int /*<<< orphan*/  pcb_fpustate; int /*<<< orphan*/ * pcb_fpusaved; } ;

/* Variables and functions */
 size_t PCB_LR ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ fork_trampoline ; 

void
cpu_fork_kthread_handler(struct thread *td, void (*func)(void *), void *arg)
{

	td->td_pcb->pcb_x[8] = (uintptr_t)func;
	td->td_pcb->pcb_x[9] = (uintptr_t)arg;
	td->td_pcb->pcb_x[PCB_LR] = (uintptr_t)fork_trampoline;
	td->td_pcb->pcb_sp = (uintptr_t)td->td_frame;
	td->td_pcb->pcb_fpusaved = &td->td_pcb->pcb_fpustate;
	td->td_pcb->pcb_vfpcpu = UINT_MAX;
}