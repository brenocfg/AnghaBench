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
 int /*<<< orphan*/  AR8327_PORT_HOL_CTRL1_EG_MIRROR_EN ; 
 int /*<<< orphan*/  AR8327_PORT_LOOKUP_ING_MIRROR_EN ; 
 int /*<<< orphan*/  AR8327_REG_PORT_HOL_CTRL1 (int) ; 
 int /*<<< orphan*/  AR8327_REG_PORT_LOOKUP (int) ; 
 int /*<<< orphan*/  arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar8327_port_disable_mirror(struct arswitch_softc *sc, int port)
{

	arswitch_modifyreg(sc->sc_dev,
	    AR8327_REG_PORT_LOOKUP(port),
	    AR8327_PORT_LOOKUP_ING_MIRROR_EN,
	    0);
	arswitch_modifyreg(sc->sc_dev,
	    AR8327_REG_PORT_HOL_CTRL1(port),
	    AR8327_PORT_HOL_CTRL1_EG_MIRROR_EN,
	    0);
}