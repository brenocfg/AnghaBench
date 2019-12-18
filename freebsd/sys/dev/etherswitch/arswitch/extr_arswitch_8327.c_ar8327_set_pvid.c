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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int AR8327_PORT_VLAN0_DEF_CVID_S ; 
 int AR8327_PORT_VLAN0_DEF_SVID_S ; 
 int /*<<< orphan*/  AR8327_REG_PORT_VLAN0 (int) ; 
 int /*<<< orphan*/  arswitch_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8327_set_pvid(struct arswitch_softc *sc, int port, int pvid)
{
	uint32_t t;

	/* Limit pvid to valid values */
	pvid &= 0x7f;

	t = pvid << AR8327_PORT_VLAN0_DEF_SVID_S;
	t |= pvid << AR8327_PORT_VLAN0_DEF_CVID_S;
	arswitch_writereg(sc->sc_dev, AR8327_REG_PORT_VLAN0(port), t);

	return (0);
}