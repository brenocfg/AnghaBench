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
struct iommu_batch {unsigned long prot; unsigned long entry; scalar_t__ npages; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_batch ; 
 struct iommu_batch* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iommu_batch_start(struct device *dev, unsigned long prot, unsigned long entry)
{
	struct iommu_batch *p = this_cpu_ptr(&iommu_batch);

	p->dev		= dev;
	p->prot		= prot;
	p->entry	= entry;
	p->npages	= 0;
}