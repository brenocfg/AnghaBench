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
struct xdma_iommu {int /*<<< orphan*/  dev; int /*<<< orphan*/  vmem; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDMA_IOMMU_RELEASE (int /*<<< orphan*/ ,struct xdma_iommu*) ; 
 int /*<<< orphan*/  pmap_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_destroy (int /*<<< orphan*/ ) ; 

int
xdma_iommu_release(struct xdma_iommu *xio)
{

	pmap_release(&xio->p);

	vmem_destroy(xio->vmem);

	XDMA_IOMMU_RELEASE(xio->dev, xio);

	return (0);
}