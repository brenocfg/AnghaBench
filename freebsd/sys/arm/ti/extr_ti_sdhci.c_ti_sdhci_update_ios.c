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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_sdhci_softc {int dummy; } ;
struct mmc_ios {scalar_t__ bus_width; scalar_t__ bus_mode; } ;
struct TYPE_2__ {struct mmc_ios ios; } ;
struct sdhci_slot {TYPE_1__ host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMCHS_CON ; 
 int /*<<< orphan*/  MMCHS_CON_DW8 ; 
 int /*<<< orphan*/  MMCHS_CON_OD ; 
 scalar_t__ bus_width_8 ; 
 struct sdhci_slot* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ opendrain ; 
 int sdhci_generic_update_ios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mmchs_read_4 (struct ti_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mmchs_write_4 (struct ti_sdhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_sdhci_update_ios(device_t brdev, device_t reqdev)
{
	struct ti_sdhci_softc *sc = device_get_softc(brdev);
	struct sdhci_slot *slot;
	struct mmc_ios *ios;
	uint32_t val32, newval32;

	slot = device_get_ivars(reqdev);
	ios = &slot->host.ios;

	/*
	 * There is an 8-bit-bus bit in the MMCHS control register which, when
	 * set, overrides the 1 vs 4 bit setting in the standard SDHCI
	 * registers.  Set that bit first according to whether an 8-bit bus is
	 * requested, then let the standard driver handle everything else.
	 */
	val32 = ti_mmchs_read_4(sc, MMCHS_CON);
	newval32  = val32;

	if (ios->bus_width == bus_width_8)
		newval32 |= MMCHS_CON_DW8;
	else
		newval32 &= ~MMCHS_CON_DW8;

	if (ios->bus_mode == opendrain)
		newval32 |= MMCHS_CON_OD;
	else /* if (ios->bus_mode == pushpull) */
		newval32 &= ~MMCHS_CON_OD;

	if (newval32 != val32)
		ti_mmchs_write_4(sc, MMCHS_CON, newval32);

	return (sdhci_generic_update_ios(brdev, reqdev));
}