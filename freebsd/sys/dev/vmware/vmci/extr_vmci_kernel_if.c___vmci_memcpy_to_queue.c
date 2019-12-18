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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
struct vmci_queue_kernel_if {TYPE_1__* dmas; } ;
struct vmci_queue {struct vmci_queue_kernel_if* kernel_if; } ;
struct iovec {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 size_t MIN (size_t,size_t) ; 
 size_t PAGE_SIZE ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vmci_memcpy_fromiovec (int /*<<< orphan*/ *,struct iovec*,size_t) ; 

__attribute__((used)) static int
__vmci_memcpy_to_queue(struct vmci_queue *queue, uint64_t queue_offset,
    const void *src, size_t size, bool is_iovec)
{
	struct vmci_queue_kernel_if *kernel_if = queue->kernel_if;
	size_t bytes_copied = 0;

	while (bytes_copied < size) {
		const uint64_t page_index =
		    (queue_offset + bytes_copied) / PAGE_SIZE;
		const size_t page_offset =
		    (queue_offset + bytes_copied) & (PAGE_SIZE - 1);
		void *va;
		size_t to_copy;

		/* Skip header. */
		va = (void *)kernel_if->dmas[page_index + 1].dma_vaddr;

		ASSERT(va);
		/*
		 * Fill up the page if we have enough payload, or else
		 * copy the remaining bytes.
		 */
		to_copy = MIN(PAGE_SIZE - page_offset, size - bytes_copied);

		if (is_iovec) {
			struct iovec *iov = (struct iovec *)src;

			/* The iovec will track bytes_copied internally. */
			vmci_memcpy_fromiovec((uint8_t *)va + page_offset,
			    iov, to_copy);
		} else
			memcpy((uint8_t *)va + page_offset,
			    (uint8_t *)src + bytes_copied, to_copy);
		bytes_copied += to_copy;
	}

	return (VMCI_SUCCESS);
}