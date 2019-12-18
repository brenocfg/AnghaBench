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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_sdhci_softc {scalar_t__ force_card_present; scalar_t__ disable_highspeed; } ;
struct sdhci_slot {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  RD4 (struct ti_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_CAN_DO_HISPD ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CARD_PRESENT ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
ti_sdhci_read_4(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct ti_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32;

	val32 = RD4(sc, off);

	/*
	 * If we need to disallow highspeed mode due to the OMAP4 erratum, strip
	 * that flag from the returned capabilities.
	 */
	if (off == SDHCI_CAPABILITIES && sc->disable_highspeed)
		val32 &= ~SDHCI_CAN_DO_HISPD;

	/*
	 * Force the card-present state if necessary.
	 */
	if (off == SDHCI_PRESENT_STATE && sc->force_card_present)
		val32 |= SDHCI_CARD_PRESENT;

	return (val32);
}