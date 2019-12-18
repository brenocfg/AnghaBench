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
struct mmc_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  squelched; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MMC_ERR_NONE ; 
 int MMC_OCR_CCS ; 
 int /*<<< orphan*/  SD_MMC_CARD_ID_FREQUENCY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mmc_calculate_clock (struct mmc_softc*) ; 
 scalar_t__ mmc_debug ; 
 int /*<<< orphan*/  mmc_delete_cards (struct mmc_softc*,int) ; 
 int /*<<< orphan*/  mmc_discover_cards (struct mmc_softc*) ; 
 int /*<<< orphan*/  mmc_idle_cards (struct mmc_softc*) ; 
 int /*<<< orphan*/  mmc_power_down (struct mmc_softc*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_softc*) ; 
 int /*<<< orphan*/  mmc_rescan_cards (struct mmc_softc*) ; 
 int /*<<< orphan*/  mmc_select_vdd (struct mmc_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_send_app_op_cond (struct mmc_softc*,int,int /*<<< orphan*/ *) ; 
 int mmc_send_if_cond (struct mmc_softc*,int) ; 
 scalar_t__ mmc_send_op_cond (struct mmc_softc*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ mmcbr_get_mode (int /*<<< orphan*/ ) ; 
 int mmcbr_get_ocr (int /*<<< orphan*/ ) ; 
 scalar_t__ mmcbr_get_power_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_bus_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_set_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmcbr_set_ocr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcbr_update_ios (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_mmc ; 
 scalar_t__ mode_sd ; 
 int /*<<< orphan*/  opendrain ; 
 scalar_t__ power_on ; 
 int /*<<< orphan*/  pushpull ; 

__attribute__((used)) static void
mmc_go_discovery(struct mmc_softc *sc)
{
	uint32_t ocr;
	device_t dev;
	int err;

	dev = sc->dev;
	if (mmcbr_get_power_mode(dev) != power_on) {
		/*
		 * First, try SD modes
		 */
		sc->squelched++; /* Errors are expected, squelch reporting. */
		mmcbr_set_mode(dev, mode_sd);
		mmc_power_up(sc);
		mmcbr_set_bus_mode(dev, pushpull);
		if (bootverbose || mmc_debug)
			device_printf(sc->dev, "Probing bus\n");
		mmc_idle_cards(sc);
		err = mmc_send_if_cond(sc, 1);
		if ((bootverbose || mmc_debug) && err == 0)
			device_printf(sc->dev,
			    "SD 2.0 interface conditions: OK\n");
		if (mmc_send_app_op_cond(sc, 0, &ocr) != MMC_ERR_NONE) {
			if (bootverbose || mmc_debug)
				device_printf(sc->dev, "SD probe: failed\n");
			/*
			 * Failed, try MMC
			 */
			mmcbr_set_mode(dev, mode_mmc);
			if (mmc_send_op_cond(sc, 0, &ocr) != MMC_ERR_NONE) {
				if (bootverbose || mmc_debug)
					device_printf(sc->dev,
					    "MMC probe: failed\n");
				ocr = 0; /* Failed both, powerdown. */
			} else if (bootverbose || mmc_debug)
				device_printf(sc->dev,
				    "MMC probe: OK (OCR: 0x%08x)\n", ocr);
		} else if (bootverbose || mmc_debug)
			device_printf(sc->dev, "SD probe: OK (OCR: 0x%08x)\n",
			    ocr);
		sc->squelched--;

		mmcbr_set_ocr(dev, mmc_select_vdd(sc, ocr));
		if (mmcbr_get_ocr(dev) != 0)
			mmc_idle_cards(sc);
	} else {
		mmcbr_set_bus_mode(dev, opendrain);
		mmcbr_set_clock(dev, SD_MMC_CARD_ID_FREQUENCY);
		mmcbr_update_ios(dev);
		/* XXX recompute vdd based on new cards? */
	}
	/*
	 * Make sure that we have a mutually agreeable voltage to at least
	 * one card on the bus.
	 */
	if (bootverbose || mmc_debug)
		device_printf(sc->dev, "Current OCR: 0x%08x\n",
		    mmcbr_get_ocr(dev));
	if (mmcbr_get_ocr(dev) == 0) {
		device_printf(sc->dev, "No compatible cards found on bus\n");
		(void)mmc_delete_cards(sc, false);
		mmc_power_down(sc);
		return;
	}
	/*
	 * Reselect the cards after we've idled them above.
	 */
	if (mmcbr_get_mode(dev) == mode_sd) {
		err = mmc_send_if_cond(sc, 1);
		mmc_send_app_op_cond(sc,
		    (err ? 0 : MMC_OCR_CCS) | mmcbr_get_ocr(dev), NULL);
	} else
		mmc_send_op_cond(sc, MMC_OCR_CCS | mmcbr_get_ocr(dev), NULL);
	mmc_discover_cards(sc);
	mmc_rescan_cards(sc);

	mmcbr_set_bus_mode(dev, pushpull);
	mmcbr_update_ios(dev);
	mmc_calculate_clock(sc);
}