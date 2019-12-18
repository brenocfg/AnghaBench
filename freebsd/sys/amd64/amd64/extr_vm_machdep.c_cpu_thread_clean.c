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
typedef  scalar_t__ vm_offset_t ;
struct thread {struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/ * pcb_tssp; } ;

/* Variables and functions */
 scalar_t__ IOPAGES ; 
 scalar_t__ ctob (scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_pti_remove_kva (scalar_t__,scalar_t__) ; 

void
cpu_thread_clean(struct thread *td)
{
	struct pcb *pcb;

	pcb = td->td_pcb;

	/*
	 * Clean TSS/iomap
	 */
	if (pcb->pcb_tssp != NULL) {
		pmap_pti_remove_kva((vm_offset_t)pcb->pcb_tssp,
		    (vm_offset_t)pcb->pcb_tssp + ctob(IOPAGES + 1));
		kmem_free((vm_offset_t)pcb->pcb_tssp, ctob(IOPAGES + 1));
		pcb->pcb_tssp = NULL;
	}
}