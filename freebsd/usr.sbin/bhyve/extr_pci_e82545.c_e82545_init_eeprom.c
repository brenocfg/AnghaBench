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
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__* octet; } ;
struct e82545_softc {int* eeprom_data; TYPE_1__ esc_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int E82545_DEV_ID_82545EM_COPPER ; 
 int E82545_SUBDEV_ID ; 
 void* E82545_VENDOR_ID_INTEL ; 
 int NVM_CHECKSUM_REG ; 
 size_t NVM_DEV_ID ; 
 size_t NVM_MAC_ADDR ; 
 size_t NVM_SUB_DEV_ID ; 
 size_t NVM_SUB_VEN_ID ; 
 int NVM_SUM ; 
 size_t NVM_VEN_ID ; 

__attribute__((used)) static void
e82545_init_eeprom(struct e82545_softc *sc)
{
	uint16_t checksum, i;

        /* mac addr */
	sc->eeprom_data[NVM_MAC_ADDR] = ((uint16_t)sc->esc_mac.octet[0]) |
		(((uint16_t)sc->esc_mac.octet[1]) << 8);
	sc->eeprom_data[NVM_MAC_ADDR+1] = ((uint16_t)sc->esc_mac.octet[2]) |
		(((uint16_t)sc->esc_mac.octet[3]) << 8);
	sc->eeprom_data[NVM_MAC_ADDR+2] = ((uint16_t)sc->esc_mac.octet[4]) |
		(((uint16_t)sc->esc_mac.octet[5]) << 8);

	/* pci ids */
	sc->eeprom_data[NVM_SUB_DEV_ID] = E82545_SUBDEV_ID;
	sc->eeprom_data[NVM_SUB_VEN_ID] = E82545_VENDOR_ID_INTEL;
	sc->eeprom_data[NVM_DEV_ID] = E82545_DEV_ID_82545EM_COPPER;
	sc->eeprom_data[NVM_VEN_ID] = E82545_VENDOR_ID_INTEL;

	/* fill in the checksum */
        checksum = 0;
	for (i = 0; i < NVM_CHECKSUM_REG; i++) {
		checksum += sc->eeprom_data[i];
	}
	checksum = NVM_SUM - checksum;
	sc->eeprom_data[NVM_CHECKSUM_REG] = checksum;
	DPRINTF("eeprom checksum: 0x%x\r\n", checksum);
}