#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* arswitch_vlan_set_pvid ) (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct arswitch_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ hal; } ;
struct TYPE_5__ {int es_flags; int /*<<< orphan*/  es_port; int /*<<< orphan*/  es_pvid; } ;
typedef  TYPE_2__ etherswitch_port_t ;

/* Variables and functions */
 int AR8X16_PORT_CTRL_DOUBLE_TAG ; 
 int AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_ADD ; 
 int AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT ; 
 int AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_STRIP ; 
 int /*<<< orphan*/  AR8X16_REG_PORT_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int EINVAL ; 
 int ETHERSWITCH_PORT_ADDTAG ; 
 int ETHERSWITCH_PORT_DOUBLE_TAG ; 
 int ETHERSWITCH_PORT_STRIPTAG ; 
 int arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8xxx_port_vlan_setup(struct arswitch_softc *sc, etherswitch_port_t *p)
{
	uint32_t reg;
	int err;

	ARSWITCH_LOCK(sc);

	/* Set the PVID. */
	if (p->es_pvid != 0)
		sc->hal.arswitch_vlan_set_pvid(sc, p->es_port, p->es_pvid);

	/* Mutually exclusive. */
	if (p->es_flags & ETHERSWITCH_PORT_ADDTAG &&
	    p->es_flags & ETHERSWITCH_PORT_STRIPTAG) {
		ARSWITCH_UNLOCK(sc);
		return (EINVAL);
	}

	reg = 0;
	if (p->es_flags & ETHERSWITCH_PORT_DOUBLE_TAG)
		reg |= AR8X16_PORT_CTRL_DOUBLE_TAG;
	if (p->es_flags & ETHERSWITCH_PORT_ADDTAG)
		reg |= AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_ADD <<
		    AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT;
	if (p->es_flags & ETHERSWITCH_PORT_STRIPTAG)
		reg |= AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_STRIP <<
		    AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT;

	err = arswitch_modifyreg(sc->sc_dev,
	    AR8X16_REG_PORT_CTRL(p->es_port),
	    0x3 << AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT |
	    AR8X16_PORT_CTRL_DOUBLE_TAG, reg);

	ARSWITCH_UNLOCK(sc);
	return (err);
}