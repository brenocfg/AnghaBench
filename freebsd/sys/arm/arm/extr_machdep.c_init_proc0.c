#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_5__ {int /*<<< orphan*/  fpscr; } ;
struct pcb {int pcb_vfpcpu; TYPE_1__ pcb_vfpstate; scalar_t__ pcb_flags; } ;
struct TYPE_7__ {struct pcb* pc_curpcb; } ;
struct TYPE_6__ {int td_kstack_pages; struct pcb* td_pcb; int /*<<< orphan*/ * td_frame; scalar_t__ td_kstack; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VFPSCR_DN ; 
 int kstack_pages ; 
 TYPE_4__* pcpup ; 
 int /*<<< orphan*/  proc0 ; 
 int /*<<< orphan*/  proc0_tf ; 
 int /*<<< orphan*/  proc_linkup0 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__ thread0 ; 

void
init_proc0(vm_offset_t kstack)
{
	proc_linkup0(&proc0, &thread0);
	thread0.td_kstack = kstack;
	thread0.td_kstack_pages = kstack_pages;
	thread0.td_pcb = (struct pcb *)(thread0.td_kstack +
	    thread0.td_kstack_pages * PAGE_SIZE) - 1;
	thread0.td_pcb->pcb_flags = 0;
	thread0.td_pcb->pcb_vfpcpu = -1;
	thread0.td_pcb->pcb_vfpstate.fpscr = VFPSCR_DN;
	thread0.td_frame = &proc0_tf;
	pcpup->pc_curpcb = thread0.td_pcb;
}