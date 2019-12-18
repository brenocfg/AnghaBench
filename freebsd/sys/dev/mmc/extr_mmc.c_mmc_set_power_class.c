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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int spec_vers; } ;
struct mmc_ivars {int bus_width; int* raw_ext_csd; int /*<<< orphan*/  cmd6_time; int /*<<< orphan*/  rca; TYPE_1__ csd; } ;
typedef  enum mmc_bus_width { ____Placeholder_mmc_bus_width } mmc_bus_width ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int /*<<< orphan*/  EXT_CSD_POWER_CLASS ; 
 int EXT_CSD_POWER_CLASS_4BIT_MASK ; 
 int EXT_CSD_POWER_CLASS_4BIT_SHIFT ; 
 int EXT_CSD_POWER_CLASS_8BIT_MASK ; 
 int EXT_CSD_POWER_CLASS_8BIT_SHIFT ; 
 size_t EXT_CSD_PWR_CL_200_195 ; 
 size_t EXT_CSD_PWR_CL_200_360 ; 
 size_t EXT_CSD_PWR_CL_200_360_DDR ; 
 size_t EXT_CSD_PWR_CL_26_195 ; 
 size_t EXT_CSD_PWR_CL_26_360 ; 
 size_t EXT_CSD_PWR_CL_52_195 ; 
 size_t EXT_CSD_PWR_CL_52_195_DDR ; 
 size_t EXT_CSD_PWR_CL_52_360 ; 
 size_t EXT_CSD_PWR_CL_52_360_DDR ; 
 int MMC_ERR_INVALID ; 
 int MMC_ERR_NONE ; 
#define  MMC_OCR_270_280 137 
#define  MMC_OCR_280_290 136 
#define  MMC_OCR_290_300 135 
#define  MMC_OCR_300_310 134 
#define  MMC_OCR_310_320 133 
#define  MMC_OCR_320_330 132 
#define  MMC_OCR_330_340 131 
#define  MMC_OCR_340_350 130 
#define  MMC_OCR_350_360 129 
#define  MMC_OCR_LOW_VOLTAGE 128 
 int /*<<< orphan*/  MMC_TYPE_HS200_HS400ES_MAX ; 
 int /*<<< orphan*/  MMC_TYPE_HS_26_MAX ; 
 int /*<<< orphan*/  MMC_TYPE_HS_52_MAX ; 
 int bus_timing_mmc_ddr52 ; 
 int bus_timing_normal ; 
 int bus_width_1 ; 
 int bus_width_4 ; 
 int bus_width_8 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int mmc_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmcbr_get_clock (int /*<<< orphan*/ ) ; 
 scalar_t__ mmcbr_get_mode (int /*<<< orphan*/ ) ; 
 int mmcbr_get_timing (int /*<<< orphan*/ ) ; 
 int mmcbr_get_vdd (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_mmc ; 

__attribute__((used)) static int
mmc_set_power_class(struct mmc_softc *sc, struct mmc_ivars *ivar)
{
	device_t dev;
	const uint8_t *ext_csd;
	uint32_t clock;
	uint8_t value;
	enum mmc_bus_timing timing;
	enum mmc_bus_width bus_width;

	dev = sc->dev;
	timing = mmcbr_get_timing(dev);
	bus_width = ivar->bus_width;
	if (mmcbr_get_mode(dev) != mode_mmc || ivar->csd.spec_vers < 4 ||
	    timing == bus_timing_normal || bus_width == bus_width_1)
		return (MMC_ERR_NONE);

	value = 0;
	ext_csd = ivar->raw_ext_csd;
	clock = mmcbr_get_clock(dev);
	switch (1 << mmcbr_get_vdd(dev)) {
	case MMC_OCR_LOW_VOLTAGE:
		if (clock <= MMC_TYPE_HS_26_MAX)
			value = ext_csd[EXT_CSD_PWR_CL_26_195];
		else if (clock <= MMC_TYPE_HS_52_MAX) {
			if (timing >= bus_timing_mmc_ddr52 &&
			    bus_width >= bus_width_4)
				value = ext_csd[EXT_CSD_PWR_CL_52_195_DDR];
			else
				value = ext_csd[EXT_CSD_PWR_CL_52_195];
		} else if (clock <= MMC_TYPE_HS200_HS400ES_MAX)
			value = ext_csd[EXT_CSD_PWR_CL_200_195];
		break;
	case MMC_OCR_270_280:
	case MMC_OCR_280_290:
	case MMC_OCR_290_300:
	case MMC_OCR_300_310:
	case MMC_OCR_310_320:
	case MMC_OCR_320_330:
	case MMC_OCR_330_340:
	case MMC_OCR_340_350:
	case MMC_OCR_350_360:
		if (clock <= MMC_TYPE_HS_26_MAX)
			value = ext_csd[EXT_CSD_PWR_CL_26_360];
		else if (clock <= MMC_TYPE_HS_52_MAX) {
			if (timing == bus_timing_mmc_ddr52 &&
			    bus_width >= bus_width_4)
				value = ext_csd[EXT_CSD_PWR_CL_52_360_DDR];
			else
				value = ext_csd[EXT_CSD_PWR_CL_52_360];
		} else if (clock <= MMC_TYPE_HS200_HS400ES_MAX) {
			if (bus_width == bus_width_8)
				value = ext_csd[EXT_CSD_PWR_CL_200_360_DDR];
			else
				value = ext_csd[EXT_CSD_PWR_CL_200_360];
		}
		break;
	default:
		device_printf(dev, "No power class support for VDD 0x%x\n",
			1 << mmcbr_get_vdd(dev));
		return (MMC_ERR_INVALID);
	}

	if (bus_width == bus_width_8)
		value = (value & EXT_CSD_POWER_CLASS_8BIT_MASK) >>
		    EXT_CSD_POWER_CLASS_8BIT_SHIFT;
	else
		value = (value & EXT_CSD_POWER_CLASS_4BIT_MASK) >>
		    EXT_CSD_POWER_CLASS_4BIT_SHIFT;

	if (value == 0)
		return (MMC_ERR_NONE);

	return (mmc_switch(dev, dev, ivar->rca, EXT_CSD_CMD_SET_NORMAL,
	    EXT_CSD_POWER_CLASS, value, ivar->cmd6_time, true));
}