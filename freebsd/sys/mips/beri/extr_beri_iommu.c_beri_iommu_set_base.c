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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct beri_iommu_softc {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_SET_BASE ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
beri_iommu_set_base(struct beri_iommu_softc *sc, vm_offset_t addr)
{

	bus_write_8(sc->res[0], IOMMU_SET_BASE, htole64(addr));
}