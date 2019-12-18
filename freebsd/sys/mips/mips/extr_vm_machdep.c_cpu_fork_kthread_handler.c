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
struct thread {TYPE_1__* td_pcb; } ;
typedef  void* register_t ;
struct TYPE_2__ {void** pcb_context; } ;

/* Variables and functions */
 size_t PCB_REG_S0 ; 
 size_t PCB_REG_S1 ; 

void
cpu_fork_kthread_handler(struct thread *td, void (*func)(void *), void *arg)
{
	/*
	 * Note that the trap frame follows the args, so the function
	 * is really called like this:	func(arg, frame);
	 */
	td->td_pcb->pcb_context[PCB_REG_S0] = (register_t)(intptr_t)func;
	td->td_pcb->pcb_context[PCB_REG_S1] = (register_t)(intptr_t)arg;
}