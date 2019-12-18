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
struct elink_phy {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_DIGITAL5_MISC6 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_warpcore_reset_lane(struct bxe_softc *sc,
				      struct elink_phy *phy,
				      uint8_t reset)
{
	uint16_t val;
	/* Take lane out of reset after configuration is finished */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_DIGITAL5_MISC6, &val);
	if (reset)
		val |= 0xC000;
	else
		val &= 0x3FFF;
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, val);
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, &val);
}