#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct pcpu {struct pcb* pc_curpcb; } ;
struct pcb {int /*<<< orphan*/  pcb_vfpcpu; int /*<<< orphan*/  pcb_fpustate; int /*<<< orphan*/ * pcb_fpusaved; scalar_t__ pcb_fpflags; } ;
struct TYPE_3__ {int td_kstack_pages; struct pcb* td_pcb; int /*<<< orphan*/ * td_frame; scalar_t__ td_kstack; } ;

/* Variables and functions */
 int KSTACK_PAGES ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct pcpu* __pcpu ; 
 int /*<<< orphan*/  proc0 ; 
 int /*<<< orphan*/  proc0_tf ; 
 int /*<<< orphan*/  proc_linkup0 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ thread0 ; 

__attribute__((used)) static void
init_proc0(vm_offset_t kstack)
{
	struct pcpu *pcpup = &__pcpu[0];

	proc_linkup0(&proc0, &thread0);
	thread0.td_kstack = kstack;
	thread0.td_kstack_pages = KSTACK_PAGES;
	thread0.td_pcb = (struct pcb *)(thread0.td_kstack +
	    thread0.td_kstack_pages * PAGE_SIZE) - 1;
	thread0.td_pcb->pcb_fpflags = 0;
	thread0.td_pcb->pcb_fpusaved = &thread0.td_pcb->pcb_fpustate;
	thread0.td_pcb->pcb_vfpcpu = UINT_MAX;
	thread0.td_frame = &proc0_tf;
	pcpup->pc_curpcb = thread0.td_pcb;
}