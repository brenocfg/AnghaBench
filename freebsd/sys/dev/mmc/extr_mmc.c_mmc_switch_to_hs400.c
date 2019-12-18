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
typedef  int /*<<< orphan*/  uint16_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_ivars {int /*<<< orphan*/  bus_width; int /*<<< orphan*/  hs_tran_speed; int /*<<< orphan*/  rca; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MMC_ERR_NONE ; 
 int bus_timing_hs ; 
 int mmc_set_card_bus_width (struct mmc_softc*,struct mmc_ivars*,int) ; 
 int mmc_set_timing (struct mmc_softc*,struct mmc_ivars*,int) ; 
 int /*<<< orphan*/  mmcbr_set_bus_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_switch_to_hs400(struct mmc_softc *sc, struct mmc_ivars *ivar,
    uint32_t clock, enum mmc_bus_timing max_timing)
{
	device_t dev;
	int err;
	uint16_t rca;

	dev = sc->dev;
	rca = ivar->rca;

	/*
	 * Both clock and timing must be set as appropriate for high speed
	 * before eventually switching to HS400/HS400ES; mmc_set_timing()
	 * will issue mmcbr_update_ios().
	 */
	mmcbr_set_clock(dev, ivar->hs_tran_speed);
	err = mmc_set_timing(sc, ivar, bus_timing_hs);
	if (err != MMC_ERR_NONE)
		return (err);

	/*
	 * Set EXT_CSD_BUS_WIDTH_8_DDR in EXT_CSD_BUS_WIDTH (and additionally
	 * EXT_CSD_BUS_WIDTH_ES for HS400ES).
	 */
	err = mmc_set_card_bus_width(sc, ivar, max_timing);
	if (err != MMC_ERR_NONE)
		return (err);
	mmcbr_set_bus_width(dev, ivar->bus_width);
	mmcbr_update_ios(dev);

	/* Finally, switch to HS400/HS400ES mode. */
	err = mmc_set_timing(sc, ivar, max_timing);
	if (err != MMC_ERR_NONE)
		return (err);
	mmcbr_set_clock(dev, clock);
	mmcbr_update_ios(dev);
	return (MMC_ERR_NONE);
}