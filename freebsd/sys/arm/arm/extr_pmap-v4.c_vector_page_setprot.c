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
struct l2_bucket {int* l2b_kva; } ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int L1_S_PROT_MASK ; 
 int L2_S_PROT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PTE_KERNEL ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 size_t l2pte_index (int /*<<< orphan*/ ) ; 
 struct l2_bucket* pmap_get_l2_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_page ; 

void
vector_page_setprot(int prot)
{
	struct l2_bucket *l2b;
	pt_entry_t *ptep;

	l2b = pmap_get_l2_bucket(kernel_pmap, vector_page);

	ptep = &l2b->l2b_kva[l2pte_index(vector_page)];

	*ptep = (*ptep & ~L1_S_PROT_MASK) | L2_S_PROT(PTE_KERNEL, prot);
	PTE_SYNC(ptep);
	cpu_tlb_flushD_SE(vector_page);
	cpu_cpwait();
}