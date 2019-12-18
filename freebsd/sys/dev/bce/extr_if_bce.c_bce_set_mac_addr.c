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
typedef  int u8 ;
typedef  int u32 ;
struct bce_softc {int* eaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_EMAC_MAC_MATCH0 ; 
 int /*<<< orphan*/  BCE_EMAC_MAC_MATCH1 ; 
 int /*<<< orphan*/  BCE_INFO_MISC ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*,int*,char*) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bce_set_mac_addr(struct bce_softc *sc)
{
	u32 val;
	u8 *mac_addr = sc->eaddr;

	/* ToDo: Add support for setting multiple MAC addresses. */

	DBENTER(BCE_VERBOSE_RESET);
	DBPRINT(sc, BCE_INFO_MISC, "Setting Ethernet address = "
	    "%6D\n", sc->eaddr, ":");

	val = (mac_addr[0] << 8) | mac_addr[1];

	REG_WR(sc, BCE_EMAC_MAC_MATCH0, val);

	val = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
	    (mac_addr[4] << 8) | mac_addr[5];

	REG_WR(sc, BCE_EMAC_MAC_MATCH1, val);

	DBEXIT(BCE_VERBOSE_RESET);
}