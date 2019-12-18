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
struct TYPE_2__ {int pcb_esi; int pcb_ebx; } ;

/* Variables and functions */

void
cpu_fork_kthread_handler(struct thread *td, void (*func)(void *), void *arg)
{
	/*
	 * Note that the trap frame follows the args, so the function
	 * is really called like this:  func(arg, frame);
	 */
	td->td_pcb->pcb_esi = (int) func;	/* function */
	td->td_pcb->pcb_ebx = (int) arg;	/* first arg */
}