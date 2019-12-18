#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mmc_ios {int bus_width; int power_mode; scalar_t__ timing; unsigned int clock; } ;
struct TYPE_3__ {struct mmc_ios ios; } ;
struct aw_mmc_softc {unsigned int aw_clock; TYPE_2__* aw_mmc_conf; int /*<<< orphan*/  aw_dev; int /*<<< orphan*/  aw_clk_mmc; int /*<<< orphan*/  aw_reg_vqmmc; int /*<<< orphan*/  aw_reg_vmmc; TYPE_1__ aw_host; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ can_calibrate; scalar_t__ new_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_MMC_BWDR ; 
 int AW_MMC_BWDR1 ; 
 int AW_MMC_BWDR4 ; 
 int AW_MMC_BWDR8 ; 
 int /*<<< orphan*/  AW_MMC_CKCR ; 
 int AW_MMC_CKCR_DIV ; 
 int /*<<< orphan*/  AW_MMC_GCTL ; 
 int AW_MMC_GCTL_DDR_MOD_SEL ; 
 int /*<<< orphan*/  AW_MMC_NTSR ; 
 int AW_MMC_NTSR_MODE_SELECT ; 
 int AW_MMC_READ_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_MMC_SAMP_DL ; 
 int AW_MMC_SAMP_DL_SW_EN ; 
 int /*<<< orphan*/  AW_MMC_WRITE_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int /*<<< orphan*/  aw_mmc_init (struct aw_mmc_softc*) ; 
 int /*<<< orphan*/  aw_mmc_reset (struct aw_mmc_softc*) ; 
 int aw_mmc_update_clock (struct aw_mmc_softc*,int) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_timing_mmc_ddr52 ; 
 scalar_t__ bus_timing_uhs_ddr50 ; 
#define  bus_width_1 133 
#define  bus_width_4 132 
#define  bus_width_8 131 
 int clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_set_freq (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct aw_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
#define  power_off 130 
#define  power_on 129 
#define  power_up 128 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_mmc_update_ios(device_t bus, device_t child)
{
	int error;
	struct aw_mmc_softc *sc;
	struct mmc_ios *ios;
	unsigned int clock;
	uint32_t reg, div = 1;

	sc = device_get_softc(bus);

	ios = &sc->aw_host.ios;

	/* Set the bus width. */
	switch (ios->bus_width) {
	case bus_width_1:
		AW_MMC_WRITE_4(sc, AW_MMC_BWDR, AW_MMC_BWDR1);
		break;
	case bus_width_4:
		AW_MMC_WRITE_4(sc, AW_MMC_BWDR, AW_MMC_BWDR4);
		break;
	case bus_width_8:
		AW_MMC_WRITE_4(sc, AW_MMC_BWDR, AW_MMC_BWDR8);
		break;
	}

	switch (ios->power_mode) {
	case power_on:
		break;
	case power_off:
		if (bootverbose)
			device_printf(sc->aw_dev, "Powering down sd/mmc\n");

		if (sc->aw_reg_vmmc)
			regulator_disable(sc->aw_reg_vmmc);
		if (sc->aw_reg_vqmmc)
			regulator_disable(sc->aw_reg_vqmmc);

		aw_mmc_reset(sc);
		break;
	case power_up:
		if (bootverbose)
			device_printf(sc->aw_dev, "Powering up sd/mmc\n");

		if (sc->aw_reg_vmmc)
			regulator_enable(sc->aw_reg_vmmc);
		if (sc->aw_reg_vqmmc)
			regulator_enable(sc->aw_reg_vqmmc);
		aw_mmc_init(sc);
		break;
	};

	/* Enable ddr mode if needed */
	reg = AW_MMC_READ_4(sc, AW_MMC_GCTL);
	if (ios->timing == bus_timing_uhs_ddr50 ||
	  ios->timing == bus_timing_mmc_ddr52)
		reg |= AW_MMC_GCTL_DDR_MOD_SEL;
	else
		reg &= ~AW_MMC_GCTL_DDR_MOD_SEL;
	AW_MMC_WRITE_4(sc, AW_MMC_GCTL, reg);

	if (ios->clock && ios->clock != sc->aw_clock) {
		sc->aw_clock = clock = ios->clock;

		/* Disable clock */
		error = aw_mmc_update_clock(sc, 0);
		if (error != 0)
			return (error);

		if (ios->timing == bus_timing_mmc_ddr52 &&
		    (sc->aw_mmc_conf->new_timing ||
		    ios->bus_width == bus_width_8)) {
			div = 2;
			clock <<= 1;
		}

		/* Reset the divider. */
		reg = AW_MMC_READ_4(sc, AW_MMC_CKCR);
		reg &= ~AW_MMC_CKCR_DIV;
		reg |= div - 1;
		AW_MMC_WRITE_4(sc, AW_MMC_CKCR, reg);

		/* New timing mode if needed */
		if (sc->aw_mmc_conf->new_timing) {
			reg = AW_MMC_READ_4(sc, AW_MMC_NTSR);
			reg |= AW_MMC_NTSR_MODE_SELECT;
			AW_MMC_WRITE_4(sc, AW_MMC_NTSR, reg);
		}

		/* Set the MMC clock. */
		error = clk_disable(sc->aw_clk_mmc);
		if (error != 0 && bootverbose)
			device_printf(sc->aw_dev,
			  "failed to disable mmc clock: %d\n", error);
		error = clk_set_freq(sc->aw_clk_mmc, clock,
		    CLK_SET_ROUND_DOWN);
		if (error != 0) {
			device_printf(sc->aw_dev,
			    "failed to set frequency to %u Hz: %d\n",
			    clock, error);
			return (error);
		}
		error = clk_enable(sc->aw_clk_mmc);
		if (error != 0 && bootverbose)
			device_printf(sc->aw_dev,
			  "failed to re-enable mmc clock: %d\n", error);

		if (sc->aw_mmc_conf->can_calibrate)
			AW_MMC_WRITE_4(sc, AW_MMC_SAMP_DL, AW_MMC_SAMP_DL_SW_EN);

		/* Enable clock. */
		error = aw_mmc_update_clock(sc, 1);
		if (error != 0)
			return (error);
	}


	return (0);
}