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
struct scatterlist {scalar_t__ length; scalar_t__ dma_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_PAGE_SIZE ; 
 unsigned long SG_ENT_PHYS_ADDRESS (struct scatterlist*) ; 
 int iommu_is_span_boundary (unsigned long,int,unsigned long,unsigned long) ; 
 int iommu_num_pages (unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_span_boundary(unsigned long entry,
				   unsigned long shift,
				   unsigned long boundary_size,
				   struct scatterlist *outs,
				   struct scatterlist *sg)
{
	unsigned long paddr = SG_ENT_PHYS_ADDRESS(outs);
	int nr = iommu_num_pages(paddr, outs->dma_length + sg->length,
				 IO_PAGE_SIZE);

	return iommu_is_span_boundary(entry, nr, shift, boundary_size);
}