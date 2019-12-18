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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ GRCBASE_UMAC0 ; 
 scalar_t__ GRCBASE_UMAC1 ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_PORT ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 scalar_t__ UMAC_REG_MAXFR ; 
 int /*<<< orphan*/  elink_cl22_read (struct bxe_softc*,struct elink_phy*,int,int*) ; 
 int /*<<< orphan*/  elink_cl22_write (struct bxe_softc*,struct elink_phy*,int,int) ; 

__attribute__((used)) static void elink_54618se_config_loopback(struct elink_phy *phy,
					  struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val;
	uint32_t umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;

	ELINK_DEBUG_P0(sc, "2PMA/PMD ext_phy_loopback: 54618se\n");

	/* Enable master/slave manual mmode and set to master */
	/* mii write 9 [bits set 11 12] */
	elink_cl22_write(sc, phy, 0x09, 3<<11);

	/* forced 1G and disable autoneg */
	/* set val [mii read 0] */
	/* set val [expr $val & [bits clear 6 12 13]] */
	/* set val [expr $val | [bits set 6 8]] */
	/* mii write 0 $val */
	elink_cl22_read(sc, phy, 0x00, &val);
	val &= ~((1<<6) | (1<<12) | (1<<13));
	val |= (1<<6) | (1<<8);
	elink_cl22_write(sc, phy, 0x00, val);

	/* Set external loopback and Tx using 6dB coding */
	/* mii write 0x18 7 */
	/* set val [mii read 0x18] */
	/* mii write 0x18 [expr $val | [bits set 10 15]] */
	elink_cl22_write(sc, phy, 0x18, 7);
	elink_cl22_read(sc, phy, 0x18, &val);
	elink_cl22_write(sc, phy, 0x18, val | (1<<10) | (1<<15));

	/* This register opens the gate for the UMAC despite its name */
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 1);

	/* Maximum Frame Length (RW). Defines a 14-Bit maximum frame
	 * length used by the MAC receive logic to check frames.
	 */
	REG_WR(sc, umac_base + UMAC_REG_MAXFR, 0x2710);
}