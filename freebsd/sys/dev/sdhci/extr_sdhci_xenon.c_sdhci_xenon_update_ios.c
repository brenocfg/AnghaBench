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
typedef  int uint32_t ;
struct sdhci_xenon_softc {int slot_id; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  reg_vqmmc; int /*<<< orphan*/  dev; } ;
struct mmc_ios {int power_mode; scalar_t__ clock; } ;
struct TYPE_2__ {struct mmc_ios ios; } ;
struct sdhci_slot {TYPE_1__ host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ SD_MMC_CARD_ID_FREQUENCY ; 
 int XENON_SDCLK_IDLEOFF_ENABLE_SHIFT ; 
 int /*<<< orphan*/  XENON_SYS_OP_CTRL ; 
 int /*<<< orphan*/  bootverbose ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sdhci_slot* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct sdhci_xenon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
#define  power_off 130 
#define  power_on 129 
#define  power_up 128 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 
 int sdhci_generic_update_ios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_xenon_phy_set (int /*<<< orphan*/ ,struct mmc_ios*) ; 

__attribute__((used)) static int
sdhci_xenon_update_ios(device_t brdev, device_t reqdev)
{
	int err;
	struct sdhci_xenon_softc *sc;
	struct mmc_ios *ios;
	struct sdhci_slot *slot;
	uint32_t reg;

	err = sdhci_generic_update_ios(brdev, reqdev);
	if (err != 0)
		return (err);

 	sc = device_get_softc(brdev);
	slot = device_get_ivars(reqdev);
 	ios = &slot->host.ios;

	switch (ios->power_mode) {
	case power_on:
		break;
	case power_off:
		if (bootverbose)
			device_printf(sc->dev, "Powering down sd/mmc\n");

		if (sc->reg_vqmmc)
			regulator_disable(sc->reg_vqmmc);
		break;
	case power_up:
		if (bootverbose)
			device_printf(sc->dev, "Powering up sd/mmc\n");

		if (sc->reg_vqmmc)
			regulator_enable(sc->reg_vqmmc);
		break;
	};

	/* Update the PHY settings. */
	if (ios->clock != 0)
		sdhci_xenon_phy_set(brdev, ios);

	if (ios->clock > SD_MMC_CARD_ID_FREQUENCY) {
		/* Enable SDCLK_IDLEOFF. */
		reg = bus_read_4(sc->mem_res, XENON_SYS_OP_CTRL);
		reg |= 1 << (XENON_SDCLK_IDLEOFF_ENABLE_SHIFT + sc->slot_id);
		bus_write_4(sc->mem_res, XENON_SYS_OP_CTRL, reg);
	}

	return (0);
}