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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmci_queue_kernel_if {size_t num_pages; struct vmci_dma_alloc* dmas; } ;
struct vmci_queue {struct vmci_queue_kernel_if* kernel_if; int /*<<< orphan*/ * q_header; int /*<<< orphan*/ * saved_header; } ;
struct vmci_dma_alloc {scalar_t__ dma_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CEILING (scalar_t__,size_t) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 size_t PAGE_SIZE ; 
 scalar_t__ VMCI_MAX_GUEST_QP_MEMORY ; 
 struct vmci_queue* malloc (size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_dma_malloc (size_t,int,struct vmci_dma_alloc*) ; 
 int /*<<< orphan*/  vmci_free_queue (struct vmci_queue*,size_t) ; 

void *
vmci_alloc_queue(uint64_t size, uint32_t flags)
{
	struct vmci_queue *queue;
	size_t i;
	const size_t num_pages = CEILING(size, PAGE_SIZE) + 1;
	const size_t dmas_size = num_pages * sizeof(struct vmci_dma_alloc);
	const size_t queue_size =
	    sizeof(*queue) + sizeof(*(queue->kernel_if)) + dmas_size;

	/* Size should be enforced by vmci_qpair_alloc(), double-check here. */
	if (size > VMCI_MAX_GUEST_QP_MEMORY) {
		ASSERT(false);
		return (NULL);
	}

	queue = malloc(queue_size, M_DEVBUF, M_NOWAIT);
	if (!queue)
		return (NULL);

	queue->q_header = NULL;
	queue->saved_header = NULL;
	queue->kernel_if = (struct vmci_queue_kernel_if *)(queue + 1);
	queue->kernel_if->num_pages = num_pages;
	queue->kernel_if->dmas = (struct vmci_dma_alloc *)(queue->kernel_if +
	    1);
	for (i = 0; i < num_pages; i++) {
		vmci_dma_malloc(PAGE_SIZE, 1, &queue->kernel_if->dmas[i]);
		if (!queue->kernel_if->dmas[i].dma_vaddr) {
			/* Size excl. the header. */
			vmci_free_queue(queue, i * PAGE_SIZE);
			return (NULL);
		}
	}

	/* Queue header is the first page. */
	queue->q_header = (void *)queue->kernel_if->dmas[0].dma_vaddr;

	return ((void *)queue);
}