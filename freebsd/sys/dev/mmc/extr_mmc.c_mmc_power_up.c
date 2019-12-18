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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
typedef  enum mmc_vccq { ____Placeholder_mmc_vccq } mmc_vccq ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SD_MMC_CARD_ID_FREQUENCY ; 
 int /*<<< orphan*/  bus_timing_normal ; 
 int /*<<< orphan*/  bus_width_1 ; 
 int /*<<< orphan*/  cs_dontcare ; 
 int /*<<< orphan*/  mmc_highest_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_ms_delay (int) ; 
 int /*<<< orphan*/  mmcbr_get_host_ocr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_bus_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_bus_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_chip_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_vccq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmcbr_set_vdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmcbr_switch_vccq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendrain ; 
 int /*<<< orphan*/  power_on ; 
 int /*<<< orphan*/  power_up ; 
 int vccq_120 ; 
 int vccq_330 ; 

__attribute__((used)) static void
mmc_power_up(struct mmc_softc *sc)
{
	device_t dev;
	enum mmc_vccq vccq;

	dev = sc->dev;
	mmcbr_set_vdd(dev, mmc_highest_voltage(mmcbr_get_host_ocr(dev)));
	mmcbr_set_bus_mode(dev, opendrain);
	mmcbr_set_chip_select(dev, cs_dontcare);
	mmcbr_set_bus_width(dev, bus_width_1);
	mmcbr_set_power_mode(dev, power_up);
	mmcbr_set_clock(dev, 0);
	mmcbr_update_ios(dev);
	for (vccq = vccq_330; ; vccq--) {
		mmcbr_set_vccq(dev, vccq);
		if (mmcbr_switch_vccq(dev) == 0 || vccq == vccq_120)
			break;
	}
	mmc_ms_delay(1);

	mmcbr_set_clock(dev, SD_MMC_CARD_ID_FREQUENCY);
	mmcbr_set_timing(dev, bus_timing_normal);
	mmcbr_set_power_mode(dev, power_on);
	mmcbr_update_ios(dev);
	mmc_ms_delay(2);
}