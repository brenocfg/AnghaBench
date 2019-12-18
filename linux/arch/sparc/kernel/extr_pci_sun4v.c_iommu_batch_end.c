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
struct iommu_batch {scalar_t__ npages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PGLIST_NENTS ; 
 int /*<<< orphan*/  iommu_batch ; 
 long iommu_batch_flush (struct iommu_batch*,int /*<<< orphan*/ ) ; 
 struct iommu_batch* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline long iommu_batch_end(u64 mask)
{
	struct iommu_batch *p = this_cpu_ptr(&iommu_batch);

	BUG_ON(p->npages >= PGLIST_NENTS);

	return iommu_batch_flush(p, mask);
}