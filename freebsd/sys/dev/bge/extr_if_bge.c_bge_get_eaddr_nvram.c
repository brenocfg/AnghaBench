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
 int BGE_EE_MAC_OFFSET ; 
 int BGE_EE_MAC_OFFSET_5906 ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int bge_read_nvram (struct bge_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_get_eaddr_nvram(struct bge_softc *sc, uint8_t ether_addr[])
{
	int mac_offset = BGE_EE_MAC_OFFSET;

	if (sc->bge_asicrev == BGE_ASICREV_BCM5906)
		mac_offset = BGE_EE_MAC_OFFSET_5906;

	return (bge_read_nvram(sc, ether_addr, mac_offset + 2,
	    ETHER_ADDR_LEN));
}