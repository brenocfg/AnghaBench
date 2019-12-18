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
struct TYPE_2__ {unsigned long owner; int frame; } ;

/* Variables and functions */
 unsigned long DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  JAZZ_R4030_TRSTBL_INV ; 
 int VDMA_PAGE (unsigned long) ; 
 int VDMA_PAGESIZE ; 
 unsigned long VDMA_PAGE_EMPTY ; 
 int VDMA_PGTBL_ENTRIES ; 
 TYPE_1__* pgtbl ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  r4030_write_reg32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vdma_debug ; 
 int /*<<< orphan*/  vdma_lock ; 

unsigned long vdma_alloc(unsigned long paddr, unsigned long size)
{
	int first, last, pages, frame, i;
	unsigned long laddr, flags;

	/* check arguments */

	if (paddr > 0x1fffffff) {
		if (vdma_debug)
			printk("vdma_alloc: Invalid physical address: %08lx\n",
			       paddr);
		return DMA_MAPPING_ERROR;	/* invalid physical address */
	}
	if (size > 0x400000 || size == 0) {
		if (vdma_debug)
			printk("vdma_alloc: Invalid size: %08lx\n", size);
		return DMA_MAPPING_ERROR;	/* invalid physical address */
	}

	spin_lock_irqsave(&vdma_lock, flags);
	/*
	 * Find free chunk
	 */
	pages = VDMA_PAGE(paddr + size) - VDMA_PAGE(paddr) + 1;
	first = 0;
	while (1) {
		while (pgtbl[first].owner != VDMA_PAGE_EMPTY &&
		       first < VDMA_PGTBL_ENTRIES) first++;
		if (first + pages > VDMA_PGTBL_ENTRIES) {	/* nothing free */
			spin_unlock_irqrestore(&vdma_lock, flags);
			return DMA_MAPPING_ERROR;
		}

		last = first + 1;
		while (pgtbl[last].owner == VDMA_PAGE_EMPTY
		       && last - first < pages)
			last++;

		if (last - first == pages)
			break;	/* found */
		first = last + 1;
	}

	/*
	 * Mark pages as allocated
	 */
	laddr = (first << 12) + (paddr & (VDMA_PAGESIZE - 1));
	frame = paddr & ~(VDMA_PAGESIZE - 1);

	for (i = first; i < last; i++) {
		pgtbl[i].frame = frame;
		pgtbl[i].owner = laddr;
		frame += VDMA_PAGESIZE;
	}

	/*
	 * Update translation table and return logical start address
	 */
	r4030_write_reg32(JAZZ_R4030_TRSTBL_INV, 0);

	if (vdma_debug > 1)
		printk("vdma_alloc: Allocated %d pages starting from %08lx\n",
		     pages, laddr);

	if (vdma_debug > 2) {
		printk("LADDR: ");
		for (i = first; i < last; i++)
			printk("%08x ", i << 12);
		printk("\nPADDR: ");
		for (i = first; i < last; i++)
			printk("%08x ", pgtbl[i].frame);
		printk("\nOWNER: ");
		for (i = first; i < last; i++)
			printk("%08x ", pgtbl[i].owner);
		printk("\n");
	}

	spin_unlock_irqrestore(&vdma_lock, flags);

	return laddr;
}