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
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; int /*<<< orphan*/  ue_eaddr; } ;
struct muge_softc {int chipid; int chiprev; int /*<<< orphan*/  sc_flags; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_MAX_LEN ; 
 int /*<<< orphan*/  ETH_BULK_IN_DLY ; 
 int /*<<< orphan*/  ETH_BURST_CAP ; 
 int /*<<< orphan*/  ETH_FCT_FLOW ; 
 int /*<<< orphan*/  ETH_FCT_RX_CTL ; 
 int /*<<< orphan*/  ETH_FCT_RX_FIFO_END ; 
 int /*<<< orphan*/  ETH_FCT_TX_CTL ; 
 int ETH_FCT_TX_CTL_EN_ ; 
 int /*<<< orphan*/  ETH_FCT_TX_FIFO_END ; 
 int /*<<< orphan*/  ETH_FLOW ; 
 int /*<<< orphan*/  ETH_HW_CFG ; 
 int ETH_HW_CFG_LRST_ ; 
 int ETH_HW_CFG_MEF_ ; 
 int /*<<< orphan*/  ETH_ID_REV ; 
#define  ETH_ID_REV_CHIP_ID_7800_ 131 
#define  ETH_ID_REV_CHIP_ID_7850_ 130 
 int ETH_ID_REV_CHIP_ID_MASK_ ; 
 int ETH_ID_REV_CHIP_REV_MASK_ ; 
 int ETH_INT_ENP_PHY_INT ; 
 int /*<<< orphan*/  ETH_INT_EP_CTL ; 
 int /*<<< orphan*/  ETH_INT_STS ; 
 int ETH_INT_STS_CLEAR_ALL_ ; 
 int /*<<< orphan*/  ETH_MAC_CR ; 
 int ETH_MAC_CR_AUTO_DUPLEX_ ; 
 int ETH_MAC_CR_AUTO_SPEED_ ; 
 int /*<<< orphan*/  ETH_MAC_RX ; 
 int ETH_MAC_RX_EN_ ; 
 int /*<<< orphan*/  ETH_MAC_TX ; 
 int ETH_MAC_TX_TXEN_ ; 
 int /*<<< orphan*/  ETH_PMT_CTL ; 
 int ETH_PMT_CTL_PHY_RST_ ; 
 int /*<<< orphan*/  ETH_RFE_CTL ; 
 int ETH_RFE_CTL_BCAST_EN_ ; 
 int ETH_RFE_CTL_DA_PERFECT_ ; 
 int /*<<< orphan*/  ETH_USB_CFG0 ; 
 int ETH_USB_CFG_BCE_ ; 
 int ETH_USB_CFG_BIR_ ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MUGE_DEFAULT_BULK_IN_DELAY ; 
 int MUGE_DEFAULT_BURST_CAP_SIZE ; 
 int /*<<< orphan*/  MUGE_FLAG_INIT_DONE ; 
 int MUGE_FS_USB_PKT_SIZE ; 
 int MUGE_HS_USB_PKT_SIZE ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int MUGE_MAX_RX_FIFO_SIZE ; 
 int MUGE_MAX_TX_FIFO_SIZE ; 
 int MUGE_SS_USB_PKT_SIZE ; 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  lan78xx_eeprom_present (struct muge_softc*) ; 
 int lan78xx_phy_init (struct muge_softc*) ; 
 int lan78xx_read_reg (struct muge_softc*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_set_rx_max_frame_length (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int lan78xx_setmacaddress (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int lan78xx_wait_for_bits (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  muge_err_printf (struct muge_softc*,char*,int) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*,...) ; 
 int usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lan78xx_chip_init(struct muge_softc *sc)
{
	int err;
	uint32_t buf;
	uint32_t burst_cap;

	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	/* Enter H/W config mode. */
	lan78xx_write_reg(sc, ETH_HW_CFG, ETH_HW_CFG_LRST_);

	if ((err = lan78xx_wait_for_bits(sc, ETH_HW_CFG, ETH_HW_CFG_LRST_)) !=
	    0) {
		muge_warn_printf(sc,
		    "timed-out waiting for lite reset to complete\n");
		goto init_failed;
	}

	/* Set the mac address. */
	if ((err = lan78xx_setmacaddress(sc, sc->sc_ue.ue_eaddr)) != 0) {
		muge_warn_printf(sc, "failed to set the MAC address\n");
		goto init_failed;
	}

	/* Read and display the revision register. */
	if ((err = lan78xx_read_reg(sc, ETH_ID_REV, &buf)) < 0) {
		muge_warn_printf(sc, "failed to read ETH_ID_REV (err = %d)\n",
		    err);
		goto init_failed;
	}
	sc->chipid = (buf & ETH_ID_REV_CHIP_ID_MASK_) >> 16;
	sc->chiprev = buf & ETH_ID_REV_CHIP_REV_MASK_;
	switch (sc->chipid) {
	case ETH_ID_REV_CHIP_ID_7800_:
	case ETH_ID_REV_CHIP_ID_7850_:
		break;
	default:
		muge_warn_printf(sc, "Chip ID 0x%04x not yet supported\n",
		    sc->chipid);
		goto init_failed;
	}
	device_printf(sc->sc_ue.ue_dev, "Chip ID 0x%04x rev %04x\n", sc->chipid,
	    sc->chiprev);

	/* Respond to BULK-IN tokens with a NAK when RX FIFO is empty. */
	if ((err = lan78xx_read_reg(sc, ETH_USB_CFG0, &buf)) != 0) {
		muge_warn_printf(sc, "failed to read ETH_USB_CFG0 (err=%d)\n", err);
		goto init_failed;
	}
	buf |= ETH_USB_CFG_BIR_;
	lan78xx_write_reg(sc, ETH_USB_CFG0, buf);

	/*
	 * XXX LTM support will go here.
	 */

	/* Configuring the burst cap. */
	switch (usbd_get_speed(sc->sc_ue.ue_udev)) {
	case USB_SPEED_SUPER:
		burst_cap = MUGE_DEFAULT_BURST_CAP_SIZE/MUGE_SS_USB_PKT_SIZE;
		break;
	case USB_SPEED_HIGH:
		burst_cap = MUGE_DEFAULT_BURST_CAP_SIZE/MUGE_HS_USB_PKT_SIZE;
		break;
	default:
		burst_cap = MUGE_DEFAULT_BURST_CAP_SIZE/MUGE_FS_USB_PKT_SIZE;
	}

	lan78xx_write_reg(sc, ETH_BURST_CAP, burst_cap);

	/* Set the default bulk in delay (same value from Linux driver). */
	lan78xx_write_reg(sc, ETH_BULK_IN_DLY, MUGE_DEFAULT_BULK_IN_DELAY);

	/* Multiple ethernet frames per USB packets. */
	err = lan78xx_read_reg(sc, ETH_HW_CFG, &buf);
	buf |= ETH_HW_CFG_MEF_;
	err = lan78xx_write_reg(sc, ETH_HW_CFG, buf);

	/* Enable burst cap. */
	if ((err = lan78xx_read_reg(sc, ETH_USB_CFG0, &buf)) < 0) {
		muge_warn_printf(sc, "failed to read ETH_USB_CFG0 (err=%d)\n",
		    err);
		goto init_failed;
	}
	buf |= ETH_USB_CFG_BCE_;
	err = lan78xx_write_reg(sc, ETH_USB_CFG0, buf);

	/*
	 * Set FCL's RX and TX FIFO sizes: according to data sheet this is
	 * already the default value. But we initialize it to the same value
	 * anyways, as that's what the Linux driver does.
	 *
	 */
	buf = (MUGE_MAX_RX_FIFO_SIZE - 512) / 512;
	err = lan78xx_write_reg(sc, ETH_FCT_RX_FIFO_END, buf);

	buf = (MUGE_MAX_TX_FIFO_SIZE - 512) / 512;
	err = lan78xx_write_reg(sc, ETH_FCT_TX_FIFO_END, buf);

	/* Enabling interrupts. (Not using them for now) */
	err = lan78xx_write_reg(sc, ETH_INT_STS, ETH_INT_STS_CLEAR_ALL_);

	/*
	 * Initializing flow control registers to 0.  These registers are
	 * properly set is handled in link-reset function in the Linux driver.
	 */
	err = lan78xx_write_reg(sc, ETH_FLOW, 0);
	err = lan78xx_write_reg(sc, ETH_FCT_FLOW, 0);

	/*
	 * Settings for the RFE, we enable broadcast and destination address
	 * perfect filtering.
	 */
	err = lan78xx_read_reg(sc, ETH_RFE_CTL, &buf);
	buf |= ETH_RFE_CTL_BCAST_EN_ | ETH_RFE_CTL_DA_PERFECT_;
	err = lan78xx_write_reg(sc, ETH_RFE_CTL, buf);

	/*
	 * At this point the Linux driver writes multicast tables, and enables
	 * checksum engines. But in FreeBSD that gets done in muge_init,
	 * which gets called when the interface is brought up.
	 */

	/* Reset the PHY. */
	lan78xx_write_reg(sc, ETH_PMT_CTL, ETH_PMT_CTL_PHY_RST_);
	if ((err = lan78xx_wait_for_bits(sc, ETH_PMT_CTL,
	    ETH_PMT_CTL_PHY_RST_)) != 0) {
		muge_warn_printf(sc,
		    "timed-out waiting for phy reset to complete\n");
		goto init_failed;
	}

	err = lan78xx_read_reg(sc, ETH_MAC_CR, &buf);
	if (sc->chipid == ETH_ID_REV_CHIP_ID_7800_ &&
	    !lan78xx_eeprom_present(sc)) {
		/* Set automatic duplex and speed on LAN7800 without EEPROM. */
		buf |= ETH_MAC_CR_AUTO_DUPLEX_ | ETH_MAC_CR_AUTO_SPEED_;
	}
	err = lan78xx_write_reg(sc, ETH_MAC_CR, buf);

	/*
	 * Enable PHY interrupts (Not really getting used for now)
	 * ETH_INT_EP_CTL: interrupt endpoint control register
	 * phy events cause interrupts to be issued
	 */
	err = lan78xx_read_reg(sc, ETH_INT_EP_CTL, &buf);
	buf |= ETH_INT_ENP_PHY_INT;
	err = lan78xx_write_reg(sc, ETH_INT_EP_CTL, buf);

	/*
	 * Enables mac's transmitter.  It will transmit frames from the buffer
	 * onto the cable.
	 */
	err = lan78xx_read_reg(sc, ETH_MAC_TX, &buf);
	buf |= ETH_MAC_TX_TXEN_;
	err = lan78xx_write_reg(sc, ETH_MAC_TX, buf);

	/* FIFO is capable of transmitting frames to MAC. */
	err = lan78xx_read_reg(sc, ETH_FCT_TX_CTL, &buf);
	buf |= ETH_FCT_TX_CTL_EN_;
	err = lan78xx_write_reg(sc, ETH_FCT_TX_CTL, buf);

	/*
	 * Set max frame length.  In linux this is dev->mtu (which by default
	 * is 1500) + VLAN_ETH_HLEN = 1518.
	 */
	err = lan78xx_set_rx_max_frame_length(sc, ETHER_MAX_LEN);

	/* Initialise the PHY. */
	if ((err = lan78xx_phy_init(sc)) != 0)
		goto init_failed;

	/* Enable MAC RX. */
	err = lan78xx_read_reg(sc, ETH_MAC_RX, &buf);
	buf |= ETH_MAC_RX_EN_;
	err = lan78xx_write_reg(sc, ETH_MAC_RX, buf);

	/* Enable FIFO controller RX. */
	err = lan78xx_read_reg(sc, ETH_FCT_RX_CTL, &buf);
	buf |= ETH_FCT_TX_CTL_EN_;
	err = lan78xx_write_reg(sc, ETH_FCT_RX_CTL, buf);

	sc->sc_flags |= MUGE_FLAG_INIT_DONE;
	return (0);

init_failed:
	muge_err_printf(sc, "lan78xx_chip_init failed (err=%d)\n", err);
	return (err);
}