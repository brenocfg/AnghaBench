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
typedef  int /*<<< orphan*/  u64 ;
struct iommu_batch {unsigned long entry; unsigned long npages; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_batch ; 
 int /*<<< orphan*/  iommu_batch_flush (struct iommu_batch*,int /*<<< orphan*/ ) ; 
 struct iommu_batch* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iommu_batch_new_entry(unsigned long entry, u64 mask)
{
	struct iommu_batch *p = this_cpu_ptr(&iommu_batch);

	if (p->entry + p->npages == entry)
		return;
	if (p->entry != ~0UL)
		iommu_batch_flush(p, mask);
	p->entry = entry;
}