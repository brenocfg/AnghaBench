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
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7101_RESET ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void elink_sfx7101_sp_sw_reset(struct bxe_softc *sc, struct elink_phy *phy)
{
	uint16_t val, cnt;

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_7101_RESET, &val);

	for (cnt = 0; cnt < 10; cnt++) {
		DELAY(1000 * 50);
		/* Writes a self-clearing reset */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_7101_RESET,
				 (val | (1<<15)));
		/* Wait for clear */
		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_7101_RESET, &val);

		if ((val & (1<<15)) == 0)
			break;
	}
}