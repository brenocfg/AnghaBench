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
 int /*<<< orphan*/  AR8327_REG_PORT_VLAN0 (int) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_VID_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int arswitch_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8327_get_pvid(struct arswitch_softc *sc, int port, int *pvid)
{
	uint32_t reg;

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * XXX for now, assuming it's CVID; likely very wrong!
	 */
	port = port & ETHERSWITCH_VID_MASK;
	reg = arswitch_readreg(sc->sc_dev, AR8327_REG_PORT_VLAN0(port));
	reg = reg >> AR8327_PORT_VLAN0_DEF_CVID_S;
	reg = reg & 0xfff;

	*pvid = reg;
	return (0);
}