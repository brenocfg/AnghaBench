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
struct fw_iso_buffer {size_t page_count; int /*<<< orphan*/ * pages; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ page_private (int /*<<< orphan*/ ) ; 

size_t fw_iso_buffer_lookup(struct fw_iso_buffer *buffer, dma_addr_t completed)
{
	size_t i;
	dma_addr_t address;
	ssize_t offset;

	for (i = 0; i < buffer->page_count; i++) {
		address = page_private(buffer->pages[i]);
		offset = (ssize_t)completed - (ssize_t)address;
		if (offset > 0 && offset <= PAGE_SIZE)
			return (i << PAGE_SHIFT) + offset;
	}

	return 0;
}