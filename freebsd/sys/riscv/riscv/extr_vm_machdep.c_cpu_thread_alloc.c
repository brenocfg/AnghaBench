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
struct trapframe {int dummy; } ;
struct thread {int td_kstack_pages; struct pcb* td_pcb; struct trapframe* td_frame; scalar_t__ td_kstack; } ;
struct pcb {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ STACKALIGN (scalar_t__) ; 

void
cpu_thread_alloc(struct thread *td)
{

	td->td_pcb = (struct pcb *)(td->td_kstack +
	    td->td_kstack_pages * PAGE_SIZE) - 1;
	td->td_frame = (struct trapframe *)STACKALIGN(
	    (caddr_t)td->td_pcb - 8 - sizeof(struct trapframe));
}