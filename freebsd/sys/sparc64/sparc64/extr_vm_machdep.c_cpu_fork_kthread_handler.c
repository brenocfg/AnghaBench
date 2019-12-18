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
typedef  void* u_long ;
struct thread {struct pcb* td_pcb; } ;
struct pcb {scalar_t__ pcb_sp; } ;
struct frame {void** fr_local; } ;

/* Variables and functions */
 scalar_t__ SPOFF ; 

void
cpu_fork_kthread_handler(struct thread *td, void (*func)(void *), void *arg)
{
	struct frame *fp;
	struct pcb *pcb;

	pcb = td->td_pcb;
	fp = (struct frame *)(pcb->pcb_sp + SPOFF);
	fp->fr_local[0] = (u_long)func;
	fp->fr_local[1] = (u_long)arg;
}