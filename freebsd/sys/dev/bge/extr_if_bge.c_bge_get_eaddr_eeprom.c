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
typedef  int /*<<< orphan*/  uint8_t ;
struct bge_softc {scalar_t__ bge_asicrev; } ;

/* Variables and functions */
 scalar_t__ BGE_ASICREV_BCM5906 ; 
 scalar_t__ BGE_EE_MAC_OFFSET ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int bge_read_eeprom (struct bge_softc*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_get_eaddr_eeprom(struct bge_softc *sc, uint8_t ether_addr[])
{

	if (sc->bge_asicrev == BGE_ASICREV_BCM5906)
		return (1);

	return (bge_read_eeprom(sc, ether_addr, BGE_EE_MAC_OFFSET + 2,
	   ETHER_ADDR_LEN));
}