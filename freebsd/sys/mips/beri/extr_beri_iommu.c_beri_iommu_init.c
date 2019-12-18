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
struct TYPE_2__ {scalar_t__ pm_segtab; } ;
struct xdma_iommu {TYPE_1__ p; } ;
struct beri_iommu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  beri_iommu_set_base (struct beri_iommu_softc*,uintptr_t) ; 
 struct beri_iommu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_iommu_init(device_t dev, struct xdma_iommu *xio)
{
	struct beri_iommu_softc *sc;

	sc = device_get_softc(dev);

	beri_iommu_set_base(sc, (uintptr_t)xio->p.pm_segtab);

	return (0);
}