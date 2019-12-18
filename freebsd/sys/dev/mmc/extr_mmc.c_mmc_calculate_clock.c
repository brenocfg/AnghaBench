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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mmc_softc {int child_count; int /*<<< orphan*/ * child_list; int /*<<< orphan*/  dev; } ;
struct mmc_ivars {int timings; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  rca; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MMC_ERR_NONE ; 
 scalar_t__ bootverbose ; 
 int bus_timing_max ; 
 int bus_timing_mmc_ddr52 ; 
 int bus_timing_mmc_hs200 ; 
 int bus_timing_mmc_hs400 ; 
 int bus_timing_mmc_hs400es ; 
 int bus_timing_normal ; 
 struct mmc_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ isclr (int*,int) ; 
 scalar_t__ isset (int*,int) ; 
 scalar_t__ mmc_debug ; 
 scalar_t__ mmc_host_timing (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmc_select_card (struct mmc_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_set_card_bus_width (struct mmc_softc*,struct mmc_ivars*,int) ; 
 scalar_t__ mmc_set_power_class (struct mmc_softc*,struct mmc_ivars*) ; 
 scalar_t__ mmc_set_timing (struct mmc_softc*,struct mmc_ivars*,int) ; 
 scalar_t__ mmc_set_vccq (struct mmc_softc*,struct mmc_ivars*,int) ; 
 scalar_t__ mmc_switch_to_hs400 (struct mmc_softc*,struct mmc_ivars*,int,int) ; 
 int mmc_timing_to_dtr (struct mmc_ivars*,int) ; 
 int /*<<< orphan*/  mmc_timing_to_string (int) ; 
 int mmcbr_get_f_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_bus_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_clock (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmcbr_tune (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_calculate_clock(struct mmc_softc *sc)
{
	device_t dev;
	struct mmc_ivars *ivar;
	int i;
	uint32_t dtr, max_dtr;
	uint16_t rca;
	enum mmc_bus_timing max_timing, timing;
	bool changed, hs400;

	dev = sc->dev;
	max_dtr = mmcbr_get_f_max(dev);
	max_timing = bus_timing_max;
	do {
		changed = false;
		for (i = 0; i < sc->child_count; i++) {
			ivar = device_get_ivars(sc->child_list[i]);
			if (isclr(&ivar->timings, max_timing) ||
			    !mmc_host_timing(dev, max_timing)) {
				for (timing = max_timing - 1; timing >=
				    bus_timing_normal; timing--) {
					if (isset(&ivar->timings, timing) &&
					    mmc_host_timing(dev, timing)) {
						max_timing = timing;
						break;
					}
				}
				changed = true;
			}
			dtr = mmc_timing_to_dtr(ivar, max_timing);
			if (dtr < max_dtr) {
				max_dtr = dtr;
				changed = true;
			}
		}
	} while (changed == true);

	if (bootverbose || mmc_debug) {
		device_printf(dev,
		    "setting transfer rate to %d.%03dMHz (%s timing)\n",
		    max_dtr / 1000000, (max_dtr / 1000) % 1000,
		    mmc_timing_to_string(max_timing));
	}

	/*
	 * HS400 must be tuned in HS200 mode, so in case of HS400 we begin
	 * with HS200 following the sequence as described in "6.6.2.2 HS200
	 * timing mode selection" of the eMMC specification v5.1, too, and
	 * switch to max_timing later.  HS400ES requires no tuning and, thus,
	 * can be switch to directly, but requires the same detour via high
	 * speed mode as does HS400 (see mmc_switch_to_hs400()).
	 */
	hs400 = max_timing == bus_timing_mmc_hs400;
	timing = hs400 == true ? bus_timing_mmc_hs200 : max_timing;
	for (i = 0; i < sc->child_count; i++) {
		ivar = device_get_ivars(sc->child_list[i]);
		if ((ivar->timings & ~(1 << bus_timing_normal)) == 0)
			goto clock;

		rca = ivar->rca;
		if (mmc_select_card(sc, rca) != MMC_ERR_NONE) {
			device_printf(dev, "Card at relative address %d "
			    "failed to select\n", rca);
			continue;
		}

		if (timing == bus_timing_mmc_hs200 ||	/* includes HS400 */
		    timing == bus_timing_mmc_hs400es) {
			if (mmc_set_vccq(sc, ivar, timing) != MMC_ERR_NONE) {
				device_printf(dev, "Failed to set VCCQ for "
				    "card at relative address %d\n", rca);
				continue;
			}
		}

		if (timing == bus_timing_mmc_hs200) {	/* includes HS400 */
			/* Set bus width (required for initial tuning). */
			if (mmc_set_card_bus_width(sc, ivar, timing) !=
			    MMC_ERR_NONE) {
				device_printf(dev, "Card at relative address "
				    "%d failed to set bus width\n", rca);
				continue;
			}
			mmcbr_set_bus_width(dev, ivar->bus_width);
			mmcbr_update_ios(dev);
		} else if (timing == bus_timing_mmc_hs400es) {
			if (mmc_switch_to_hs400(sc, ivar, max_dtr, timing) !=
			    MMC_ERR_NONE) {
				device_printf(dev, "Card at relative address "
				    "%d failed to set %s timing\n", rca,
				    mmc_timing_to_string(timing));
				continue;
			}
			goto power_class;
		}

		if (mmc_set_timing(sc, ivar, timing) != MMC_ERR_NONE) {
			device_printf(dev, "Card at relative address %d "
			    "failed to set %s timing\n", rca,
			    mmc_timing_to_string(timing));
			continue;
		}

		if (timing == bus_timing_mmc_ddr52) {
			/*
			 * Set EXT_CSD_BUS_WIDTH_n_DDR in EXT_CSD_BUS_WIDTH
			 * (must be done after switching to EXT_CSD_HS_TIMING).
			 */
			if (mmc_set_card_bus_width(sc, ivar, timing) !=
			    MMC_ERR_NONE) {
				device_printf(dev, "Card at relative address "
				    "%d failed to set bus width\n", rca);
				continue;
			}
			mmcbr_set_bus_width(dev, ivar->bus_width);
			mmcbr_update_ios(dev);
			if (mmc_set_vccq(sc, ivar, timing) != MMC_ERR_NONE) {
				device_printf(dev, "Failed to set VCCQ for "
				    "card at relative address %d\n", rca);
				continue;
			}
		}

clock:
		/* Set clock (must be done before initial tuning). */
		mmcbr_set_clock(dev, max_dtr);
		mmcbr_update_ios(dev);

		if (mmcbr_tune(dev, hs400) != 0) {
			device_printf(dev, "Card at relative address %d "
			    "failed to execute initial tuning\n", rca);
			continue;
		}

		if (hs400 == true && mmc_switch_to_hs400(sc, ivar, max_dtr,
		    max_timing) != MMC_ERR_NONE) {
			device_printf(dev, "Card at relative address %d "
			    "failed to set %s timing\n", rca,
			    mmc_timing_to_string(max_timing));
			continue;
		}

power_class:
		if (mmc_set_power_class(sc, ivar) != MMC_ERR_NONE) {
			device_printf(dev, "Card at relative address %d "
			    "failed to set power class\n", rca);
		}
	}
	(void)mmc_select_card(sc, 0);
	return (max_dtr);
}