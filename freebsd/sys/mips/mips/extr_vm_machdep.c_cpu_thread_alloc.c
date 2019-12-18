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
struct TYPE_2__ {int* md_upte; } ;
struct thread {int td_kstack; int td_kstack_pages; TYPE_1__ td_md; struct pcb* td_pcb; int /*<<< orphan*/ * td_frame; } ;
struct pcb {int /*<<< orphan*/  pcb_regs; } ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KSTACK_PAGES ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TLBLO_SWBITS_MASK ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int* pmap_pte (int /*<<< orphan*/ ,int) ; 

void
cpu_thread_alloc(struct thread *td)
{
	pt_entry_t *pte;
	int i;

	KASSERT((td->td_kstack & (1 << PAGE_SHIFT)) == 0, ("kernel stack must be aligned."));
	td->td_pcb = (struct pcb *)(td->td_kstack +
	    td->td_kstack_pages * PAGE_SIZE) - 1;
	td->td_frame = &td->td_pcb->pcb_regs;

	for (i = 0; i < KSTACK_PAGES; i++) {
		pte = pmap_pte(kernel_pmap, td->td_kstack + i * PAGE_SIZE);
		td->td_md.md_upte[i] = *pte & ~TLBLO_SWBITS_MASK;
	}
}