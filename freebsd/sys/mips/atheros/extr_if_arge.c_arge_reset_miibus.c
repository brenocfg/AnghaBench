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
typedef  int uint32_t ;
struct arge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_MAC_MII_CFG ; 
 int /*<<< orphan*/  ARGE_WRITE (struct arge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MAC_MII_CFG_RESET ; 
 int arge_fetch_mdiobus_clock_rate (struct arge_softc*) ; 

__attribute__((used)) static void
arge_reset_miibus(struct arge_softc *sc)
{
	uint32_t mdio_div;

	mdio_div = arge_fetch_mdiobus_clock_rate(sc);

	/*
	 * XXX AR934x and later; should we be also resetting the
	 * MDIO block(s) using the reset register block?
	 */

	/* Reset MII bus; program in the default divisor */
	ARGE_WRITE(sc, AR71XX_MAC_MII_CFG, MAC_MII_CFG_RESET | mdio_div);
	DELAY(100);
	ARGE_WRITE(sc, AR71XX_MAC_MII_CFG, mdio_div);
	DELAY(100);
}