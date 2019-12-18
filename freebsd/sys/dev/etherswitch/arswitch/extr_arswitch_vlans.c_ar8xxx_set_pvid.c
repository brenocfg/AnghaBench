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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8X16_REG_PORT_VLAN (int) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
ar8xxx_set_pvid(struct arswitch_softc *sc, int port, int pvid)
{

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	return (arswitch_modifyreg(sc->sc_dev,
	    AR8X16_REG_PORT_VLAN(port), 0xfff, pvid));
}