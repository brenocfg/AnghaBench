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
typedef  int u64 ;
struct iommu_table {scalar_t__ it_base; } ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int TCE_READ_SHIFT ; 
 int TCE_RPN_MASK ; 
 int TCE_RPN_SHIFT ; 
 int TCE_WRITE_SHIFT ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  flush_tce (int*) ; 
 int virt_to_bus (void*) ; 

void tce_build(struct iommu_table *tbl, unsigned long index,
	unsigned int npages, unsigned long uaddr, int direction)
{
	u64* tp;
	u64 t;
	u64 rpn;

	t = (1 << TCE_READ_SHIFT);
	if (direction != DMA_TO_DEVICE)
		t |= (1 << TCE_WRITE_SHIFT);

	tp = ((u64*)tbl->it_base) + index;

	while (npages--) {
		rpn = (virt_to_bus((void*)uaddr)) >> PAGE_SHIFT;
		t &= ~TCE_RPN_MASK;
		t |= (rpn << TCE_RPN_SHIFT);

		*tp = cpu_to_be64(t);
		flush_tce(tp);

		uaddr += PAGE_SIZE;
		tp++;
	}
}