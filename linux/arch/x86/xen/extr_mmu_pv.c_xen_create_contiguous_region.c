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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  maddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int MAX_CONTIG_ORDER ; 
 unsigned int PAGE_SIZE ; 
 unsigned long* discontig_frames ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__ virt_to_machine (unsigned long) ; 
 unsigned long virt_to_pfn (unsigned long) ; 
 int xen_exchange_memory (unsigned long,int /*<<< orphan*/ ,unsigned long*,int,unsigned int,unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  xen_remap_exchanged_ptes (unsigned long,unsigned int,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  xen_reservation_lock ; 
 int /*<<< orphan*/  xen_zap_pfn_range (unsigned long,unsigned int,unsigned long*,int /*<<< orphan*/ *) ; 

int xen_create_contiguous_region(phys_addr_t pstart, unsigned int order,
				 unsigned int address_bits,
				 dma_addr_t *dma_handle)
{
	unsigned long *in_frames = discontig_frames, out_frame;
	unsigned long  flags;
	int            success;
	unsigned long vstart = (unsigned long)phys_to_virt(pstart);

	/*
	 * Currently an auto-translated guest will not perform I/O, nor will
	 * it require PAE page directories below 4GB. Therefore any calls to
	 * this function are redundant and can be ignored.
	 */

	if (unlikely(order > MAX_CONTIG_ORDER))
		return -ENOMEM;

	memset((void *) vstart, 0, PAGE_SIZE << order);

	spin_lock_irqsave(&xen_reservation_lock, flags);

	/* 1. Zap current PTEs, remembering MFNs. */
	xen_zap_pfn_range(vstart, order, in_frames, NULL);

	/* 2. Get a new contiguous memory extent. */
	out_frame = virt_to_pfn(vstart);
	success = xen_exchange_memory(1UL << order, 0, in_frames,
				      1, order, &out_frame,
				      address_bits);

	/* 3. Map the new extent in place of old pages. */
	if (success)
		xen_remap_exchanged_ptes(vstart, order, NULL, out_frame);
	else
		xen_remap_exchanged_ptes(vstart, order, in_frames, 0);

	spin_unlock_irqrestore(&xen_reservation_lock, flags);

	*dma_handle = virt_to_machine(vstart).maddr;
	return success ? 0 : -ENOMEM;
}