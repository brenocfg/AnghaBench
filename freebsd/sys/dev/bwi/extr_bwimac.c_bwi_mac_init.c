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
struct TYPE_3__ {int rw_rev; scalar_t__ rw_type; } ;
struct bwi_softc {int sc_pwron_delay; int (* sc_init_tx_ring ) (struct bwi_softc*,int) ;int (* sc_init_rx_ring ) (struct bwi_softc*) ;int (* sc_init_txstats ) (struct bwi_softc*) ;int /*<<< orphan*/  sc_dev; TYPE_1__ sc_bus_regwin; } ;
struct TYPE_4__ {int /*<<< orphan*/  rf_ant_mode; } ;
struct bwi_mac {int mac_rev; int mac_flags; TYPE_2__ mac_rf; int /*<<< orphan*/  mac_regwin; int /*<<< orphan*/  mac_phy; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int BWI_BBP_ATTEN ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int BWI_COMM_MOBJ_MACREV ; 
 int /*<<< orphan*/  BWI_CONF_LO ; 
 int /*<<< orphan*/  BWI_CONF_LO_REQTO ; 
 int /*<<< orphan*/  BWI_CONF_LO_REQTO_MASK ; 
 int /*<<< orphan*/  BWI_CONF_LO_SERVTO ; 
 int /*<<< orphan*/  BWI_CONF_LO_SERVTO_MASK ; 
 int BWI_INTR_TIMER1 ; 
 int BWI_MAC_F_HAS_TXSTATS ; 
 int BWI_MAC_F_INITED ; 
 int BWI_MAC_INTR_STATUS ; 
 int BWI_MAC_POWERUP_DELAY ; 
 int BWI_MAC_STATUS ; 
 int BWI_MAC_STATUS_IHREN ; 
 int BWI_MAC_STATUS_UCODE_JUMP0 ; 
 scalar_t__ BWI_REGWIN_T_BUSPCIE ; 
 int /*<<< orphan*/  BWI_STATE_LO ; 
 int BWI_TXRX_INTR_MASK (int) ; 
 scalar_t__ BWI_TXRX_IS_RX (int) ; 
 int BWI_TXRX_NRING ; 
 int BWI_TXRX_RX_INTRS ; 
 int BWI_TXRX_TX_INTRS ; 
 int BWI_TX_NRING ; 
 int /*<<< orphan*/  CSR_SETBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,int,int) ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int,int) ; 
 int __SHIFTIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bwi_bus_init (struct bwi_softc*,struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_bss_param_init (struct bwi_mac*) ; 
 int bwi_mac_fw_init (struct bwi_mac*) ; 
 int bwi_mac_fw_load (struct bwi_mac*) ; 
 int bwi_mac_gpio_init (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_hostflags_init (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_opmode_init (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_reset (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  bwi_mac_setup_tpctl (struct bwi_mac*) ; 
 int bwi_phy_calibrate (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_phy_clear_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_phy_init (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_regwin_is_enabled (struct bwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_rf_clear_state (TYPE_2__*) ; 
 int /*<<< orphan*/  bwi_rf_on (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_set_ant_mode (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (struct bwi_softc*,int) ; 
 int stub2 (struct bwi_softc*) ; 
 int stub3 (struct bwi_softc*) ; 

int
bwi_mac_init(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	int error, i;

	/* Clear MAC/PHY/RF states */
	bwi_mac_setup_tpctl(mac);
	bwi_rf_clear_state(&mac->mac_rf);
	bwi_phy_clear_state(&mac->mac_phy);

	/* Enable MAC and linked it to PHY */
	if (!bwi_regwin_is_enabled(sc, &mac->mac_regwin))
		bwi_mac_reset(mac, 1);

	/* Initialize backplane */
	error = bwi_bus_init(sc, mac);
	if (error)
		return error;

	/* do timeout fixup */
	if (sc->sc_bus_regwin.rw_rev <= 5 &&
	    sc->sc_bus_regwin.rw_type != BWI_REGWIN_T_BUSPCIE) {
		CSR_SETBITS_4(sc, BWI_CONF_LO,
		__SHIFTIN(BWI_CONF_LO_SERVTO, BWI_CONF_LO_SERVTO_MASK) |
		__SHIFTIN(BWI_CONF_LO_REQTO, BWI_CONF_LO_REQTO_MASK));
	}

	/* Calibrate PHY */
	error = bwi_phy_calibrate(mac);
	if (error) {
		device_printf(sc->sc_dev, "PHY calibrate failed\n");
		return error;
	}

	/* Prepare to initialize firmware */
	CSR_WRITE_4(sc, BWI_MAC_STATUS,
		    BWI_MAC_STATUS_UCODE_JUMP0 |
		    BWI_MAC_STATUS_IHREN);

	/*
	 * Load and initialize firmwares
	 */
	error = bwi_mac_fw_load(mac);
	if (error)
		return error;

	error = bwi_mac_gpio_init(mac);
	if (error)
		return error;

	error = bwi_mac_fw_init(mac);
	if (error)
		return error;

	/*
	 * Turn on RF
	 */
	bwi_rf_on(mac);

	/* TODO: LED, hardware rf enabled is only related to LED setting */

	/*
	 * Initialize PHY
	 */
	CSR_WRITE_2(sc, BWI_BBP_ATTEN, 0);
	bwi_phy_init(mac);

	/* TODO: interference mitigation */

	/*
	 * Setup antenna mode
	 */
	bwi_rf_set_ant_mode(mac, mac->mac_rf.rf_ant_mode);

	/*
	 * Initialize operation mode (RX configuration)
	 */
	bwi_mac_opmode_init(mac);

	/* set up Beacon interval */
	if (mac->mac_rev < 3) {
		CSR_WRITE_2(sc, 0x60e, 0);
		CSR_WRITE_2(sc, 0x610, 0x8000);
		CSR_WRITE_2(sc, 0x604, 0);
		CSR_WRITE_2(sc, 0x606, 0x200);
	} else {
		CSR_WRITE_4(sc, 0x188, 0x80000000);
		CSR_WRITE_4(sc, 0x18c, 0x2000000);
	}

	/*
	 * Initialize TX/RX interrupts' mask
	 */
	CSR_WRITE_4(sc, BWI_MAC_INTR_STATUS, BWI_INTR_TIMER1);
	for (i = 0; i < BWI_TXRX_NRING; ++i) {
		uint32_t intrs;

		if (BWI_TXRX_IS_RX(i))
			intrs = BWI_TXRX_RX_INTRS;
		else
			intrs = BWI_TXRX_TX_INTRS;
		CSR_WRITE_4(sc, BWI_TXRX_INTR_MASK(i), intrs);
	}

	/* allow the MAC to control the PHY clock (dynamic on/off) */
	CSR_SETBITS_4(sc, BWI_STATE_LO, 0x100000);

	/* Setup MAC power up delay */
	CSR_WRITE_2(sc, BWI_MAC_POWERUP_DELAY, sc->sc_pwron_delay);

	/* Set MAC regwin revision */
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_MACREV, mac->mac_rev);

	/*
	 * Initialize host flags
	 */
	bwi_mac_hostflags_init(mac);

	/*
	 * Initialize BSS parameters
	 */
	bwi_mac_bss_param_init(mac);

	/*
	 * Initialize TX rings
	 */
	for (i = 0; i < BWI_TX_NRING; ++i) {
		error = sc->sc_init_tx_ring(sc, i);
		if (error) {
			device_printf(sc->sc_dev,
				  "can't initialize %dth TX ring\n", i);
			return error;
		}
	}

	/*
	 * Initialize RX ring
	 */
	error = sc->sc_init_rx_ring(sc);
	if (error) {
		device_printf(sc->sc_dev, "can't initialize RX ring\n");
		return error;
	}

	/*
	 * Initialize TX stats if the current MAC uses that
	 */
	if (mac->mac_flags & BWI_MAC_F_HAS_TXSTATS) {
		error = sc->sc_init_txstats(sc);
		if (error) {
			device_printf(sc->sc_dev,
				  "can't initialize TX stats ring\n");
			return error;
		}
	}

	/* update PRETBTT */
	CSR_WRITE_2(sc, 0x612, 0x50);	/* Force Pre-TBTT to 80? */
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, 0x416, 0x50);
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, 0x414, 0x1f4);

	mac->mac_flags |= BWI_MAC_F_INITED;
	return 0;
}