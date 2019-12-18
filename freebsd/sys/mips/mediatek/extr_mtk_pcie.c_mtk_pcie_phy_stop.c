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
struct mtk_pci_softc {scalar_t__ socid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ MTK_SOC_MT7621 ; 
 int SYSCTL_MT7621_REV_E ; 
 int /*<<< orphan*/  SYSCTL_REVID ; 
 int SYSCTL_REVID_MASK ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_clock_disable_all (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_reset_assert_all (int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_reset_deassert_all (int /*<<< orphan*/ ) ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pcie_phy_stop(device_t dev)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);

	if (sc->socid == MTK_SOC_MT7621 &&
	    (mtk_sysctl_get(SYSCTL_REVID) & SYSCTL_REVID_MASK) !=
	    SYSCTL_MT7621_REV_E) {
		if (fdt_reset_deassert_all(dev))
			return (ENXIO);
	} else {
		if (fdt_reset_assert_all(dev))
			return (ENXIO);
	}

	if (fdt_clock_disable_all(dev))
		return (ENXIO);

	return (0);
}