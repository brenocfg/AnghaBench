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
 int /*<<< orphan*/  AR8327_REG_PORT_LOOKUP (int) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int ETHERSWITCH_VID_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ar8327_vlan_set_port(struct arswitch_softc *sc, uint32_t ports, int vid)
{
	int err, port;

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);

	/* For port based vlans the vlanid is the same as the port index. */
	port = vid & ETHERSWITCH_VID_MASK;

	err = arswitch_modifyreg(sc->sc_dev, AR8327_REG_PORT_LOOKUP(port),
	    0x7f, /* vlan membership mask */
	    (ports & 0x7f));

	if (err)
		return (err);
	return (0);
}