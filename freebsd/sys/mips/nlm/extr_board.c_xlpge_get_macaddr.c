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

/* Variables and functions */
 size_t EEPROM_MACADDR_OFFSET ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/ * board_eeprom_buf ; 
 scalar_t__ board_eeprom_set ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
xlpge_get_macaddr(uint8_t *macaddr)
{

	if (board_eeprom_set == 0) {
		/* No luck, take some reasonable value */
		macaddr[0] = 0x00; macaddr[1] = 0x0f; macaddr[2] = 0x30;
		macaddr[3] = 0x20; macaddr[4] = 0x0d; macaddr[5] = 0x5b;
	} else
		memcpy(macaddr, &board_eeprom_buf[EEPROM_MACADDR_OFFSET],
		    ETHER_ADDR_LEN);
}