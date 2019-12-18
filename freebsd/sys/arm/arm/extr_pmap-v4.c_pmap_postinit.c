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
typedef  int u_int ;
struct l2_bucket {int* l2b_kva; } ;
struct l1_ttable {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 scalar_t__ L1_TABLE_SIZE ; 
 int L2_S_CACHE_MASK ; 
 int /*<<< orphan*/  M_VMPMAP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ PAGE_SIZE ; 
 int PMAP_DOMAINS ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 scalar_t__ contigmalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (scalar_t__) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 size_t l2pte_index (scalar_t__) ; 
 struct l1_ttable* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxproc ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct l2_bucket* pmap_get_l2_bucket (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_init_l1 (struct l1_ttable*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int pte_l2_s_cache_mode_pt ; 

void
pmap_postinit(void)
{
	struct l2_bucket *l2b;
	struct l1_ttable *l1;
	pd_entry_t *pl1pt;
	pt_entry_t *ptep, pte;
	vm_offset_t va, eva;
	u_int loop, needed;

	needed = (maxproc / PMAP_DOMAINS) + ((maxproc % PMAP_DOMAINS) ? 1 : 0);
	needed -= 1;
	l1 = malloc(sizeof(*l1) * needed, M_VMPMAP, M_WAITOK);

	for (loop = 0; loop < needed; loop++, l1++) {
		/* Allocate a L1 page table */
		va = (vm_offset_t)contigmalloc(L1_TABLE_SIZE, M_VMPMAP, 0, 0x0,
		    0xffffffff, L1_TABLE_SIZE, 0);

		if (va == 0)
			panic("Cannot allocate L1 KVM");

		eva = va + L1_TABLE_SIZE;
		pl1pt = (pd_entry_t *)va;

		while (va < eva) {
				l2b = pmap_get_l2_bucket(kernel_pmap, va);
				ptep = &l2b->l2b_kva[l2pte_index(va)];
				pte = *ptep;
				pte = (pte & ~L2_S_CACHE_MASK) | pte_l2_s_cache_mode_pt;
				*ptep = pte;
				PTE_SYNC(ptep);
				cpu_tlb_flushD_SE(va);

				va += PAGE_SIZE;
		}
		pmap_init_l1(l1, pl1pt);
	}


#ifdef DEBUG
	printf("pmap_postinit: Allocated %d static L1 descriptor tables\n",
	    needed);
#endif
}