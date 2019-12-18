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
struct xdma_iommu {int dummy; } ;
struct beri_iommu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  beri_iommu_set_base (struct beri_iommu_softc*,int /*<<< orphan*/ ) ; 
 struct beri_iommu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_iommu_release(device_t dev, struct xdma_iommu *xio)
{
	struct beri_iommu_softc *sc;

	sc = device_get_softc(dev);

	beri_iommu_set_base(sc, 0);

	return (0);
}