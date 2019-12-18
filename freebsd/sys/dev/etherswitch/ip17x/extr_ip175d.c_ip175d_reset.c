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
struct ip17x_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IP175D_RESET_PHY ; 
 int IP175D_RESET_REG ; 
 int /*<<< orphan*/  ip17x_updatephy (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ip17x_writephy (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ip175d_reset(struct ip17x_softc *sc)
{

	/* Reset all the switch settings. */
	ip17x_writephy(sc->sc_dev, IP175D_RESET_PHY, IP175D_RESET_REG, 0x175d);
	DELAY(2000);

	/* Disable the special tagging mode. */
	ip17x_updatephy(sc->sc_dev, 21, 22, 0x3, 0x0);

	/* Set 802.1q protocol type. */
	ip17x_writephy(sc->sc_dev, 22, 3, 0x8100);

	return (0);
}