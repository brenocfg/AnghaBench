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
struct tegra_sdhci_softc {scalar_t__ force_card_present; int /*<<< orphan*/  mem_res; } ;
struct sdhci_slot {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CARD_PRESENT ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
tegra_sdhci_read_4(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct tegra_sdhci_softc *sc;
	uint32_t val32;

	sc = device_get_softc(dev);
	val32 = bus_read_4(sc->mem_res, off);
	/* Force the card-present state if necessary. */
	if (off == SDHCI_PRESENT_STATE && sc->force_card_present)
		val32 |= SDHCI_CARD_PRESENT;
	return (val32);
}