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
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct usb_ether {int* ue_eaddr; int /*<<< orphan*/  ue_dev; } ;
struct muge_softc {int dummy; } ;
typedef  scalar_t__ mac_l ;
typedef  scalar_t__ mac_h ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_IS_VALID (int*) ; 
 int /*<<< orphan*/  ETH_E2P_MAC_OFFSET ; 
 int /*<<< orphan*/  ETH_RX_ADDRH ; 
 int /*<<< orphan*/  ETH_RX_ADDRL ; 
 int /*<<< orphan*/  OTP_MAC_OFFSET ; 
 int /*<<< orphan*/  arc4rand (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lan78xx_eeprom_present (struct muge_softc*) ; 
 scalar_t__ lan78xx_eeprom_read_raw (struct muge_softc*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ lan78xx_otp_read (struct muge_softc*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ lan78xx_read_reg (struct muge_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usb_fdt_get_mac_addr (int /*<<< orphan*/ ,struct usb_ether*) ; 

__attribute__((used)) static void
muge_set_mac_addr(struct usb_ether *ue)
{
	struct muge_softc *sc = uether_getsc(ue);
	uint32_t mac_h, mac_l;

	memset(ue->ue_eaddr, 0xff, ETHER_ADDR_LEN);

	uint32_t val;
	lan78xx_read_reg(sc, 0, &val);

	/* Read current MAC address from RX_ADDRx registers. */
	if ((lan78xx_read_reg(sc, ETH_RX_ADDRL, &mac_l) == 0) &&
	    (lan78xx_read_reg(sc, ETH_RX_ADDRH, &mac_h) == 0)) {
		ue->ue_eaddr[5] = (uint8_t)((mac_h >> 8) & 0xff);
		ue->ue_eaddr[4] = (uint8_t)((mac_h) & 0xff);
		ue->ue_eaddr[3] = (uint8_t)((mac_l >> 24) & 0xff);
		ue->ue_eaddr[2] = (uint8_t)((mac_l >> 16) & 0xff);
		ue->ue_eaddr[1] = (uint8_t)((mac_l >> 8) & 0xff);
		ue->ue_eaddr[0] = (uint8_t)((mac_l) & 0xff);
	}

	/*
	 * If RX_ADDRx did not provide a valid MAC address, try EEPROM.  If that
	 * doesn't work, try OTP.  Whether any of these methods work or not, try
	 * FDT data, because it is allowed to override the EEPROM/OTP values.
	 */
	if (ETHER_IS_VALID(ue->ue_eaddr)) {
		muge_dbg_printf(sc, "MAC assigned from registers\n");
	} else if (lan78xx_eeprom_present(sc) && lan78xx_eeprom_read_raw(sc,
	    ETH_E2P_MAC_OFFSET, ue->ue_eaddr, ETHER_ADDR_LEN) == 0 &&
	    ETHER_IS_VALID(ue->ue_eaddr)) {
		muge_dbg_printf(sc, "MAC assigned from EEPROM\n");
	} else if (lan78xx_otp_read(sc, OTP_MAC_OFFSET, ue->ue_eaddr,
	    ETHER_ADDR_LEN) == 0 && ETHER_IS_VALID(ue->ue_eaddr)) {
		muge_dbg_printf(sc, "MAC assigned from OTP\n");
	}

#ifdef FDT
	/* ue->ue_eaddr modified only if config exists for this dev instance. */
	usb_fdt_get_mac_addr(ue->ue_dev, ue);
	if (ETHER_IS_VALID(ue->ue_eaddr)) {
		muge_dbg_printf(sc, "MAC assigned from FDT data\n");
	}
#endif

	if (!ETHER_IS_VALID(ue->ue_eaddr)) {
		muge_dbg_printf(sc, "MAC assigned randomly\n");
		arc4rand(ue->ue_eaddr, ETHER_ADDR_LEN, 0);
		ue->ue_eaddr[0] &= ~0x01;	/* unicast */
		ue->ue_eaddr[0] |= 0x02;	/* locally administered */
	}
}