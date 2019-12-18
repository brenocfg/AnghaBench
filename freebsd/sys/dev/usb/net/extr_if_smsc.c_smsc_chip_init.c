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
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_eaddr; } ;
struct smsc_softc {int sc_rev_id; int sc_mac_csr; TYPE_1__ sc_ue; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int AFC_CFG_DEFAULT ; 
 scalar_t__ ETHERTYPE_VLAN ; 
 int ETHER_ALIGN ; 
 int /*<<< orphan*/  SMSC_AFC_CFG ; 
 int /*<<< orphan*/  SMSC_BULK_IN_DLY ; 
 int /*<<< orphan*/  SMSC_BURST_CAP ; 
 int /*<<< orphan*/  SMSC_FLOW ; 
 int /*<<< orphan*/  SMSC_HW_CFG ; 
 int SMSC_HW_CFG_BCE ; 
 int SMSC_HW_CFG_BIR ; 
 int SMSC_HW_CFG_LRST ; 
 int SMSC_HW_CFG_MEF ; 
 int SMSC_HW_CFG_RXDOFF ; 
 int /*<<< orphan*/  SMSC_ID_REV ; 
 int SMSC_ID_REV_CHIP_ID_MASK ; 
 int SMSC_ID_REV_CHIP_REV_MASK ; 
 int /*<<< orphan*/  SMSC_INTR_STATUS ; 
 int /*<<< orphan*/  SMSC_LED_GPIO_CFG ; 
 int SMSC_LED_GPIO_CFG_FDX_LED ; 
 int SMSC_LED_GPIO_CFG_LNK_LED ; 
 int SMSC_LED_GPIO_CFG_SPD_LED ; 
 int /*<<< orphan*/  SMSC_LOCK (struct smsc_softc*) ; 
 int /*<<< orphan*/  SMSC_MAC_CSR ; 
 int SMSC_MAC_CSR_RXEN ; 
 int SMSC_MAC_CSR_TXEN ; 
 int /*<<< orphan*/  SMSC_PM_CTRL ; 
 int SMSC_PM_CTRL_PHY_RST ; 
 int /*<<< orphan*/  SMSC_TX_CFG ; 
 int SMSC_TX_CFG_ON ; 
 int /*<<< orphan*/  SMSC_UNLOCK (struct smsc_softc*) ; 
 int /*<<< orphan*/  SMSC_VLAN1 ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc_err_printf (struct smsc_softc*,char*,int) ; 
 int smsc_phy_init (struct smsc_softc*) ; 
 int smsc_read_reg (struct smsc_softc*,int /*<<< orphan*/ ,int*) ; 
 int smsc_setmacaddress (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int smsc_wait_for_bits (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_warn_printf (struct smsc_softc*,char*,...) ; 
 int /*<<< orphan*/  smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smsc_chip_init(struct smsc_softc *sc)
{
	int err;
	int locked;
	uint32_t reg_val;
	int burst_cap;

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		SMSC_LOCK(sc);

	/* Enter H/W config mode */
	smsc_write_reg(sc, SMSC_HW_CFG, SMSC_HW_CFG_LRST);

	if ((err = smsc_wait_for_bits(sc, SMSC_HW_CFG, SMSC_HW_CFG_LRST)) != 0) {
		smsc_warn_printf(sc, "timed-out waiting for reset to complete\n");
		goto init_failed;
	}

	/* Reset the PHY */
	smsc_write_reg(sc, SMSC_PM_CTRL, SMSC_PM_CTRL_PHY_RST);

	if ((err = smsc_wait_for_bits(sc, SMSC_PM_CTRL, SMSC_PM_CTRL_PHY_RST)) != 0) {
		smsc_warn_printf(sc, "timed-out waiting for phy reset to complete\n");
		goto init_failed;
	}

	/* Set the mac address */
	if ((err = smsc_setmacaddress(sc, sc->sc_ue.ue_eaddr)) != 0) {
		smsc_warn_printf(sc, "failed to set the MAC address\n");
		goto init_failed;
	}

	/* Don't know what the HW_CFG_BIR bit is, but following the reset sequence
	 * as used in the Linux driver.
	 */
	if ((err = smsc_read_reg(sc, SMSC_HW_CFG, &reg_val)) != 0) {
		smsc_warn_printf(sc, "failed to read HW_CFG: %d\n", err);
		goto init_failed;
	}
	reg_val |= SMSC_HW_CFG_BIR;
	smsc_write_reg(sc, SMSC_HW_CFG, reg_val);

	/* There is a so called 'turbo mode' that the linux driver supports, it
	 * seems to allow you to jam multiple frames per Rx transaction.  By default
	 * this driver supports that and therefore allows multiple frames per URB.
	 *
	 * The xfer buffer size needs to reflect this as well, therefore based on
	 * the calculations in the Linux driver the RX bufsize is set to 18944,
	 *     bufsz = (16 * 1024 + 5 * 512)
	 *
	 * Burst capability is the number of URBs that can be in a burst of data/
	 * ethernet frames.
	 */
	if (usbd_get_speed(sc->sc_ue.ue_udev) == USB_SPEED_HIGH)
		burst_cap = 37;
	else
		burst_cap = 128;

	smsc_write_reg(sc, SMSC_BURST_CAP, burst_cap);

	/* Set the default bulk in delay (magic value from Linux driver) */
	smsc_write_reg(sc, SMSC_BULK_IN_DLY, 0x00002000);



	/*
	 * Initialise the RX interface
	 */
	if ((err = smsc_read_reg(sc, SMSC_HW_CFG, &reg_val)) < 0) {
		smsc_warn_printf(sc, "failed to read HW_CFG: (err = %d)\n", err);
		goto init_failed;
	}

	/* Adjust the packet offset in the buffer (designed to try and align IP
	 * header on 4 byte boundary)
	 */
	reg_val &= ~SMSC_HW_CFG_RXDOFF;
	reg_val |= (ETHER_ALIGN << 9) & SMSC_HW_CFG_RXDOFF;
	
	/* The following setings are used for 'turbo mode', a.k.a multiple frames
	 * per Rx transaction (again info taken form Linux driver).
	 */
	reg_val |= (SMSC_HW_CFG_MEF | SMSC_HW_CFG_BCE);

	smsc_write_reg(sc, SMSC_HW_CFG, reg_val);

	/* Clear the status register ? */
	smsc_write_reg(sc, SMSC_INTR_STATUS, 0xffffffff);

	/* Read and display the revision register */
	if ((err = smsc_read_reg(sc, SMSC_ID_REV, &sc->sc_rev_id)) < 0) {
		smsc_warn_printf(sc, "failed to read ID_REV (err = %d)\n", err);
		goto init_failed;
	}

	device_printf(sc->sc_ue.ue_dev, "chip 0x%04lx, rev. %04lx\n", 
	    (sc->sc_rev_id & SMSC_ID_REV_CHIP_ID_MASK) >> 16, 
	    (sc->sc_rev_id & SMSC_ID_REV_CHIP_REV_MASK));

	/* GPIO/LED setup */
	reg_val = SMSC_LED_GPIO_CFG_SPD_LED | SMSC_LED_GPIO_CFG_LNK_LED | 
	          SMSC_LED_GPIO_CFG_FDX_LED;
	smsc_write_reg(sc, SMSC_LED_GPIO_CFG, reg_val);

	/*
	 * Initialise the TX interface
	 */
	smsc_write_reg(sc, SMSC_FLOW, 0);

	smsc_write_reg(sc, SMSC_AFC_CFG, AFC_CFG_DEFAULT);

	/* Read the current MAC configuration */
	if ((err = smsc_read_reg(sc, SMSC_MAC_CSR, &sc->sc_mac_csr)) < 0) {
		smsc_warn_printf(sc, "failed to read MAC_CSR (err=%d)\n", err);
		goto init_failed;
	}
	
	/* Vlan */
	smsc_write_reg(sc, SMSC_VLAN1, (uint32_t)ETHERTYPE_VLAN);

	/*
	 * Initialise the PHY
	 */
	if ((err = smsc_phy_init(sc)) != 0)
		goto init_failed;


	/*
	 * Start TX
	 */
	sc->sc_mac_csr |= SMSC_MAC_CSR_TXEN;
	smsc_write_reg(sc, SMSC_MAC_CSR, sc->sc_mac_csr);
	smsc_write_reg(sc, SMSC_TX_CFG, SMSC_TX_CFG_ON);

	/*
	 * Start RX
	 */
	sc->sc_mac_csr |= SMSC_MAC_CSR_RXEN;
	smsc_write_reg(sc, SMSC_MAC_CSR, sc->sc_mac_csr);

	if (!locked)
		SMSC_UNLOCK(sc);

	return (0);
	
init_failed:
	if (!locked)
		SMSC_UNLOCK(sc);

	smsc_err_printf(sc, "smsc_chip_init failed (err=%d)\n", err);
	return (err);
}