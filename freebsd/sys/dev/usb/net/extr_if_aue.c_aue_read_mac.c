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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct aue_softc {int dummy; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int aue_eeprom_getword (struct aue_softc*,int) ; 

__attribute__((used)) static void
aue_read_mac(struct aue_softc *sc, uint8_t *eaddr)
{
	int i, offset;
	uint16_t word;

	for (i = 0, offset = 0; i < ETHER_ADDR_LEN / 2; i++) {
		word = aue_eeprom_getword(sc, offset + i);
		eaddr[i * 2] = (uint8_t)word;
		eaddr[i * 2 + 1] = (uint8_t)(word >> 8);
	}
}