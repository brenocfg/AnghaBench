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
struct TYPE_2__ {int /*<<< orphan*/  r_mem; } ;
struct tegra_ahci_sc {TYPE_1__ ctlr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_GHC ; 
 int AHCI_GHC_IE ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_generic_suspend (int /*<<< orphan*/ ) ; 
 struct tegra_ahci_sc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_ahci_suspend(device_t dev)
{
	struct tegra_ahci_sc *sc = device_get_softc(dev);

	bus_generic_suspend(dev);
	/* Disable interupts, so the state change(s) doesn't trigger. */
	ATA_OUTL(sc->ctlr.r_mem, AHCI_GHC,
	     ATA_INL(sc->ctlr.r_mem, AHCI_GHC) & (~AHCI_GHC_IE));
	return (0);
}