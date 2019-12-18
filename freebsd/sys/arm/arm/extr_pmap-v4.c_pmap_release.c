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
struct pcb {int /*<<< orphan*/  pcb_pagedir; int /*<<< orphan*/  pcb_dacr; int /*<<< orphan*/  pcb_l1vec; int /*<<< orphan*/ * pcb_pl1vec; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_2__ {struct pcb* td_pcb; } ;

/* Variables and functions */
 scalar_t__ KERNBASE ; 
 scalar_t__ PAGE_SIZE ; 
 struct pcb* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_domains (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_all () ; 
 int /*<<< orphan*/  cpu_setttb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct pcb* curpcb ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  pmap_free_l1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_idcache_wbinv_all (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_is_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_tlb_flushID (int /*<<< orphan*/ ) ; 
 TYPE_1__ thread0 ; 
 scalar_t__ vector_page ; 

void
pmap_release(pmap_t pmap)
{
	struct pcb *pcb;

	pmap_idcache_wbinv_all(pmap);
	cpu_l2cache_wbinv_all();
	pmap_tlb_flushID(pmap);
	cpu_cpwait();
	if (vector_page < KERNBASE) {
		struct pcb *curpcb = PCPU_GET(curpcb);
		pcb = thread0.td_pcb;
		if (pmap_is_current(pmap)) {
			/*
 			 * Frob the L1 entry corresponding to the vector
			 * page so that it contains the kernel pmap's domain
			 * number. This will ensure pmap_remove() does not
			 * pull the current vector page out from under us.
			 */
			critical_enter();
			*pcb->pcb_pl1vec = pcb->pcb_l1vec;
			cpu_domains(pcb->pcb_dacr);
			cpu_setttb(pcb->pcb_pagedir);
			critical_exit();
		}
		pmap_remove(pmap, vector_page, vector_page + PAGE_SIZE);
		/*
		 * Make sure cpu_switch(), et al, DTRT. This is safe to do
		 * since this process has no remaining mappings of its own.
		 */
		curpcb->pcb_pl1vec = pcb->pcb_pl1vec;
		curpcb->pcb_l1vec = pcb->pcb_l1vec;
		curpcb->pcb_dacr = pcb->pcb_dacr;
		curpcb->pcb_pagedir = pcb->pcb_pagedir;

	}
	pmap_free_l1(pmap);

	dprintf("pmap_release()\n");
}