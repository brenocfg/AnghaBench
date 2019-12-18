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
typedef  int uint16_t ;
struct usb_ether {void** ue_eaddr; } ;
struct axe_softc {int sc_pwrcfg; struct usb_ether sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXE_CMD_RXCTL_WRITE ; 
 int /*<<< orphan*/  AXE_CMD_SROM_READ ; 
 scalar_t__ AXE_EEPROM_772B_NODE_ID ; 
 scalar_t__ AXE_EEPROM_772B_PHY_PWRCFG ; 
 int /*<<< orphan*/  AXE_GPIO_RELOAD_EEPROM ; 
 int /*<<< orphan*/  AXE_GPIO_WRITE (int /*<<< orphan*/ ,int) ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  axe_ax88772_phywake (struct axe_softc*) ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int hz ; 
 int le16toh (int) ; 

__attribute__((used)) static void
axe_ax88772b_init(struct axe_softc *sc)
{
	struct usb_ether *ue;
	uint16_t eeprom;
	uint8_t *eaddr;
	int i;

	ue = &sc->sc_ue;
	/* Reload EEPROM. */
	AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM, hz / 32);
	/*
	 * Save PHY power saving configuration(high byte) and
	 * clear EEPROM checksum value(low byte).
	 */
	axe_cmd(sc, AXE_CMD_SROM_READ, 0, AXE_EEPROM_772B_PHY_PWRCFG, &eeprom);
	sc->sc_pwrcfg = le16toh(eeprom) & 0xFF00;

	/*
	 * Auto-loaded default station address from internal ROM is
	 * 00:00:00:00:00:00 such that an explicit access to EEPROM
	 * is required to get real station address.
	 */
	eaddr = ue->ue_eaddr;
	for (i = 0; i < ETHER_ADDR_LEN / 2; i++) {
		axe_cmd(sc, AXE_CMD_SROM_READ, 0, AXE_EEPROM_772B_NODE_ID + i,
		    &eeprom);
		eeprom = le16toh(eeprom);
		*eaddr++ = (uint8_t)(eeprom & 0xFF);
		*eaddr++ = (uint8_t)((eeprom >> 8) & 0xFF);
	}
	/* Wakeup PHY. */
	axe_ax88772_phywake(sc);
	/* Stop MAC. */
	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);
}