#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdma_iommu {int /*<<< orphan*/  vmem; int /*<<< orphan*/  dev; int /*<<< orphan*/  p; } ;
struct TYPE_3__ {struct xdma_iommu xio; } ;
typedef  TYPE_1__ xdma_channel_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XDMA_IOMMU_REMOVE (int /*<<< orphan*/ ,struct xdma_iommu*,int) ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int,int) ; 

void
xdma_iommu_remove_entry(xdma_channel_t *xchan, vm_offset_t va)
{
	struct xdma_iommu *xio;

	xio = &xchan->xio;

	va &= ~(PAGE_SIZE - 1);
	pmap_remove(&xio->p, va, va + PAGE_SIZE);

	XDMA_IOMMU_REMOVE(xio->dev, xio, va);

	vmem_free(xio->vmem, va, PAGE_SIZE);
}