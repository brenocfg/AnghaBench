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
struct pmap {int* pm_context; int /*<<< orphan*/  pm_active; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DMMU_DEMAP ; 
 int /*<<< orphan*/  ASI_IMMU_DEMAP ; 
 scalar_t__ CPU_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KERNBASE ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int TLB_DEMAP_CONTEXT ; 
 int TLB_DEMAP_PRIMARY ; 
 int /*<<< orphan*/  cpuid ; 
 size_t curcpu ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 void* ipi_tlb_context_demap (struct pmap*) ; 
 int /*<<< orphan*/  ipi_wait (void*) ; 
 int /*<<< orphan*/  stxa (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_ncontext_demap ; 

void
tlb_context_demap(struct pmap *pm)
{
	void *cookie;
	register_t s;

	/*
	 * It is important that we are not interrupted or preempted while
	 * doing the IPIs. The interrupted CPU may hold locks, and since
	 * it will wait for the CPU that sent the IPI, this can lead
	 * to a deadlock when an interrupt comes in on that CPU and it's
	 * handler tries to grab one of that locks. This will only happen for
	 * spin locks, but these IPI types are delivered even if normal
	 * interrupts are disabled, so the lock critical section will not
	 * protect the target processor from entering the IPI handler with
	 * the lock held.
	 */
	PMAP_STATS_INC(tlb_ncontext_demap);
	cookie = ipi_tlb_context_demap(pm);
	s = intr_disable();
	if (CPU_ISSET(PCPU_GET(cpuid), &pm->pm_active)) {
		KASSERT(pm->pm_context[curcpu] != -1,
		    ("tlb_context_demap: inactive pmap?"));
		stxa(TLB_DEMAP_PRIMARY | TLB_DEMAP_CONTEXT, ASI_DMMU_DEMAP, 0);
		stxa(TLB_DEMAP_PRIMARY | TLB_DEMAP_CONTEXT, ASI_IMMU_DEMAP, 0);
		flush(KERNBASE);
	}
	intr_restore(s);
	ipi_wait(cookie);
}