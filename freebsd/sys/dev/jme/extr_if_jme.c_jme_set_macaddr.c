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
typedef  int uint32_t ;
struct jme_softc {int jme_flags; int /*<<< orphan*/  jme_dev; int /*<<< orphan*/  jme_eaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int,int) ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  JME_EFUSE_EEPROM ; 
 int JME_EFUSE_EEPROM_ADDR_SHIFT ; 
 int JME_EFUSE_EEPROM_DATA_SHIFT ; 
 int JME_EFUSE_EEPROM_FUNC0 ; 
 int JME_EFUSE_EEPROM_FUNC_SHIFT ; 
 int JME_EFUSE_EEPROM_PAGE_BAR1 ; 
 int JME_EFUSE_EEPROM_PAGE_SHIFT ; 
 int JME_EFUSE_EEPROM_WRITE ; 
 int JME_FLAG_EFUSE ; 
 int JME_PAR0 ; 
 int JME_PAR1 ; 
 scalar_t__ bcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
jme_set_macaddr(struct jme_softc *sc, uint8_t *eaddr)
{
	uint32_t val;
	int i;

	if ((sc->jme_flags & JME_FLAG_EFUSE) != 0) {
		/*
		 * Avoid reprogramming station address if the address
		 * is the same as previous one.  Note, reprogrammed
		 * station address is permanent as if it was written
		 * to EEPROM. So if station address was changed by
		 * admistrator it's possible to lose factory configured
		 * address when driver fails to restore its address.
		 * (e.g. reboot or system crash)
		 */
		if (bcmp(eaddr, sc->jme_eaddr, ETHER_ADDR_LEN) != 0) {
			for (i = 0; i < ETHER_ADDR_LEN; i++) {
				val = JME_EFUSE_EEPROM_FUNC0 <<
				    JME_EFUSE_EEPROM_FUNC_SHIFT;
				val |= JME_EFUSE_EEPROM_PAGE_BAR1 <<
				    JME_EFUSE_EEPROM_PAGE_SHIFT;
				val |= (JME_PAR0 + i) <<
				    JME_EFUSE_EEPROM_ADDR_SHIFT;
				val |= eaddr[i] << JME_EFUSE_EEPROM_DATA_SHIFT;
				pci_write_config(sc->jme_dev, JME_EFUSE_EEPROM,
				    val | JME_EFUSE_EEPROM_WRITE, 4);
			}
		}
	} else {
		CSR_WRITE_4(sc, JME_PAR0,
		    eaddr[3] << 24 | eaddr[2] << 16 | eaddr[1] << 8 | eaddr[0]);
		CSR_WRITE_4(sc, JME_PAR1, eaddr[5] << 8 | eaddr[4]);
	}
}