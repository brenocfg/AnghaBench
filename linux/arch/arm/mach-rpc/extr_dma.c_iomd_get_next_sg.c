#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sgcount; TYPE_2__* sg; } ;
struct iomd_dma {unsigned long cur_addr; unsigned long dma_addr; unsigned long dma_len; unsigned long cur_len; TYPE_1__ dma; } ;
struct TYPE_5__ {unsigned long dma_address; unsigned long length; } ;

/* Variables and functions */
 unsigned long DMA_END_L ; 
 unsigned long DMA_END_S ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 unsigned long TRANSFER_SIZE ; 
 TYPE_2__* sg_next (TYPE_2__*) ; 

__attribute__((used)) static void iomd_get_next_sg(struct iomd_dma *idma)
{
	unsigned long end, offset, flags = 0;

	if (idma->dma.sg) {
		idma->cur_addr = idma->dma_addr;
		offset = idma->cur_addr & ~PAGE_MASK;

		end = offset + idma->dma_len;

		if (end > PAGE_SIZE)
			end = PAGE_SIZE;

		if (offset + TRANSFER_SIZE >= end)
			flags |= DMA_END_L;

		idma->cur_len = end - TRANSFER_SIZE;

		idma->dma_len -= end - offset;
		idma->dma_addr += end - offset;

		if (idma->dma_len == 0) {
			if (idma->dma.sgcount > 1) {
				idma->dma.sg = sg_next(idma->dma.sg);
				idma->dma_addr = idma->dma.sg->dma_address;
				idma->dma_len = idma->dma.sg->length;
				idma->dma.sgcount--;
			} else {
				idma->dma.sg = NULL;
				flags |= DMA_END_S;
			}
		}
	} else {
		flags = DMA_END_S | DMA_END_L;
		idma->cur_addr = 0;
		idma->cur_len = 0;
	}

	idma->cur_len |= flags;
}