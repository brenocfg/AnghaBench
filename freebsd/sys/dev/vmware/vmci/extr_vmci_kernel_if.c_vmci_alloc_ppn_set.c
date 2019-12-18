#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long* vmci_ppn_list ;
typedef  int uint64_t ;
struct vmci_queue {TYPE_2__* kernel_if; } ;
struct ppn_set {int initialized; int num_produce_pages; int num_consume_pages; unsigned long* produce_ppns; unsigned long* consume_ppns; } ;
typedef  int /*<<< orphan*/  pfn ;
struct TYPE_4__ {TYPE_1__* dmas; } ;
struct TYPE_3__ {unsigned long dma_paddr; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int VMCI_ERROR_ALREADY_EXISTS ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NO_MEM ; 
 int /*<<< orphan*/  VMCI_MEMORY_NORMAL ; 
 int VMCI_SUCCESS ; 
 unsigned long* vmci_alloc_kernel_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (unsigned long*,int) ; 

int
vmci_alloc_ppn_set(void *prod_q, uint64_t num_produce_pages, void *cons_q,
    uint64_t num_consume_pages, struct ppn_set *ppn_set)
{
	struct vmci_queue *consume_q = cons_q;
	struct vmci_queue *produce_q = prod_q;
	vmci_ppn_list consume_ppns;
	vmci_ppn_list produce_ppns;
	uint64_t i;

	if (!produce_q || !num_produce_pages || !consume_q ||
	    !num_consume_pages || !ppn_set)
		return (VMCI_ERROR_INVALID_ARGS);

	if (ppn_set->initialized)
		return (VMCI_ERROR_ALREADY_EXISTS);

	produce_ppns =
	    vmci_alloc_kernel_mem(num_produce_pages * sizeof(*produce_ppns),
	    VMCI_MEMORY_NORMAL);
	if (!produce_ppns)
		return (VMCI_ERROR_NO_MEM);

	consume_ppns =
	    vmci_alloc_kernel_mem(num_consume_pages * sizeof(*consume_ppns),
	    VMCI_MEMORY_NORMAL);
	if (!consume_ppns) {
		vmci_free_kernel_mem(produce_ppns,
		    num_produce_pages * sizeof(*produce_ppns));
		return (VMCI_ERROR_NO_MEM);
	}

	for (i = 0; i < num_produce_pages; i++) {
		unsigned long pfn;

		produce_ppns[i] =
		    pfn = produce_q->kernel_if->dmas[i].dma_paddr >> PAGE_SHIFT;

		/*
		 * Fail allocation if PFN isn't supported by hypervisor.
		 */

		if (sizeof(pfn) >
		    sizeof(*produce_ppns) && pfn != produce_ppns[i])
			goto ppn_error;
	}
	for (i = 0; i < num_consume_pages; i++) {
		unsigned long pfn;

		consume_ppns[i] =
		    pfn = consume_q->kernel_if->dmas[i].dma_paddr >> PAGE_SHIFT;

		/*
		 * Fail allocation if PFN isn't supported by hypervisor.
		 */

		if (sizeof(pfn) >
		    sizeof(*consume_ppns) && pfn != consume_ppns[i])
			goto ppn_error;

	}

	ppn_set->num_produce_pages = num_produce_pages;
	ppn_set->num_consume_pages = num_consume_pages;
	ppn_set->produce_ppns = produce_ppns;
	ppn_set->consume_ppns = consume_ppns;
	ppn_set->initialized = true;
	return (VMCI_SUCCESS);

ppn_error:
	vmci_free_kernel_mem(produce_ppns, num_produce_pages *
	    sizeof(*produce_ppns));
	vmci_free_kernel_mem(consume_ppns, num_consume_pages *
	    sizeof(*consume_ppns));
	return (VMCI_ERROR_INVALID_ARGS);
}