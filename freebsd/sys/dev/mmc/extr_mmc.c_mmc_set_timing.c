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
typedef  int uint8_t ;
typedef  int u_char ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_ivars {int /*<<< orphan*/  cmd6_time; int /*<<< orphan*/  rca; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int /*<<< orphan*/  EXT_CSD_HS_TIMING ; 
 int EXT_CSD_HS_TIMING_BC ; 
 int EXT_CSD_HS_TIMING_HS ; 
 int EXT_CSD_HS_TIMING_HS200 ; 
 int EXT_CSD_HS_TIMING_HS400 ; 
 int MMC_ERR_FAILED ; 
 int MMC_ERR_INVALID ; 
 int MMC_ERR_NONE ; 
 int /*<<< orphan*/  SD_SWITCH_GROUP1 ; 
 int SD_SWITCH_HS_MODE ; 
 int /*<<< orphan*/  SD_SWITCH_MODE_SET ; 
 int SD_SWITCH_NORMAL_MODE ; 
#define  bus_timing_hs 133 
#define  bus_timing_mmc_ddr52 132 
#define  bus_timing_mmc_hs200 131 
#define  bus_timing_mmc_hs400 130 
#define  bus_timing_mmc_hs400es 129 
#define  bus_timing_normal 128 
 int mmc_sd_switch (struct mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int mmc_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mmc_switch_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmcbr_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_timing (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_sd ; 

__attribute__((used)) static int
mmc_set_timing(struct mmc_softc *sc, struct mmc_ivars *ivar,
    enum mmc_bus_timing timing)
{
	u_char switch_res[64];
	uint8_t	value;
	int err;

	if (mmcbr_get_mode(sc->dev) == mode_sd) {
		switch (timing) {
		case bus_timing_normal:
			value = SD_SWITCH_NORMAL_MODE;
			break;
		case bus_timing_hs:
			value = SD_SWITCH_HS_MODE;
			break;
		default:
			return (MMC_ERR_INVALID);
		}
		err = mmc_sd_switch(sc, SD_SWITCH_MODE_SET, SD_SWITCH_GROUP1,
		    value, switch_res);
		if (err != MMC_ERR_NONE)
			return (err);
		if ((switch_res[16] & 0xf) != value)
			return (MMC_ERR_FAILED);
		mmcbr_set_timing(sc->dev, timing);
		mmcbr_update_ios(sc->dev);
	} else {
		switch (timing) {
		case bus_timing_normal:
			value = EXT_CSD_HS_TIMING_BC;
			break;
		case bus_timing_hs:
		case bus_timing_mmc_ddr52:
			value = EXT_CSD_HS_TIMING_HS;
			break;
		case bus_timing_mmc_hs200:
			value = EXT_CSD_HS_TIMING_HS200;
			break;
		case bus_timing_mmc_hs400:
		case bus_timing_mmc_hs400es:
			value = EXT_CSD_HS_TIMING_HS400;
			break;
		default:
			return (MMC_ERR_INVALID);
		}
		err = mmc_switch(sc->dev, sc->dev, ivar->rca,
		    EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING, value,
		    ivar->cmd6_time, false);
		if (err != MMC_ERR_NONE)
			return (err);
		mmcbr_set_timing(sc->dev, timing);
		mmcbr_update_ios(sc->dev);
		err = mmc_switch_status(sc->dev, sc->dev, ivar->rca,
		    ivar->cmd6_time);
	}
	return (err);
}