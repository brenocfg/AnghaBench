#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_softc {struct ath_hal* sc_ah; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  ath_hal_mci_config; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  int /*<<< orphan*/  btinfo ;
typedef  int /*<<< orphan*/  btconfig ;
struct TYPE_8__ {int bt_gpio_bt_active; int bt_gpio_bt_priority; int bt_gpio_wlan_active; int bt_active_polarity; int bt_txstate_extend; int bt_txframe_extend; int bt_quiet_collision; int bt_rxclear_polarity; int bt_priority_time; int bt_first_slot_time; int bt_hold_rxclear; int /*<<< orphan*/  bt_mode; scalar_t__ bt_time_extend; scalar_t__ bt_isolation; scalar_t__ bt_single_ant; int /*<<< orphan*/  bt_coex_config; int /*<<< orphan*/  bt_module; } ;
typedef  TYPE_2__ HAL_BT_COEX_INFO ;
typedef  TYPE_2__ HAL_BT_COEX_CONFIG ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HAL_BT_COEX_ANTENNA_DIVERSITY ; 
 int /*<<< orphan*/  HAL_BT_COEX_CFG_MCI ; 
 int /*<<< orphan*/  HAL_BT_COEX_MODE_SLOTTED ; 
 int /*<<< orphan*/  HAL_BT_COEX_STOMP_NONE ; 
 int /*<<< orphan*/  HAL_BT_MODULE_JANUS ; 
 scalar_t__ ath_btcoex_mci_attach (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_enable (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_set_config (struct ath_hal*,TYPE_2__*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_set_info (struct ath_hal*,TYPE_2__*) ; 
 int /*<<< orphan*/  ath_hal_btcoex_set_parameter (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_btcoex_set_weights (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_btcoex_supported (struct ath_hal*) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ath_btcoex_cfg_mci(struct ath_softc *sc, uint32_t mci_cfg, int do_btdiv)
{
	HAL_BT_COEX_INFO btinfo;
	HAL_BT_COEX_CONFIG btconfig;
	struct ath_hal *ah = sc->sc_ah;

	if (! ath_hal_btcoex_supported(ah))
		return (EINVAL);

	bzero(&btinfo, sizeof(btinfo));
	bzero(&btconfig, sizeof(btconfig));

	sc->sc_ah->ah_config.ath_hal_mci_config = mci_cfg;

	if (ath_btcoex_mci_attach(sc) != 0) {
		device_printf(sc->sc_dev, "Failed to setup btcoex\n");
		return (EINVAL);
	}

	btinfo.bt_module = HAL_BT_MODULE_JANUS;	/* XXX not used? */
	btinfo.bt_coex_config = HAL_BT_COEX_CFG_MCI;

	/*
	 * MCI uses a completely different interface to speak
	 * to the bluetooth module - it's a command based
	 * thing over a serial line, rather than
	 * state pins to/from the bluetooth module.
	 *
	 * So, the GPIO configuration, polarity, etc
	 * doesn't matter on MCI devices; it's just
	 * completely ignored by the HAL.
	 */
	btinfo.bt_gpio_bt_active = 4;
	btinfo.bt_gpio_bt_priority = 8;
	btinfo.bt_gpio_wlan_active = 5;

	btinfo.bt_active_polarity = 1;	/* XXX not used */
	btinfo.bt_single_ant = 0;	/* 2 antenna on WB335 */
	btinfo.bt_isolation = 0;	/* in dB, not used */

	ath_hal_btcoex_set_info(ah, &btinfo);

	btconfig.bt_time_extend = 0;
	btconfig.bt_txstate_extend = 1;	/* true */
	btconfig.bt_txframe_extend = 1;	/* true */
	btconfig.bt_mode = HAL_BT_COEX_MODE_SLOTTED;
	btconfig.bt_quiet_collision = 1;	/* true */
	btconfig.bt_rxclear_polarity = 1;	/* true */
	btconfig.bt_priority_time = 2;
	btconfig.bt_first_slot_time = 5;
	btconfig.bt_hold_rxclear = 1;	/* true */

	ath_hal_btcoex_set_config(ah, &btconfig);

	/* Enable */
	ath_hal_btcoex_enable(sc->sc_ah);

	/* Stomp */
	ath_hal_btcoex_set_weights(ah, HAL_BT_COEX_STOMP_NONE);

	/*
	 * Enable antenna diversity.
	 */
	ath_hal_btcoex_set_parameter(ah, HAL_BT_COEX_ANTENNA_DIVERSITY,
	    do_btdiv);

	return (0);
}