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
struct TYPE_4__ {int /*<<< orphan*/  (* arswitch_vlan_set_pvid ) (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct arswitch_softc {TYPE_1__ hal; } ;
struct TYPE_5__ {int /*<<< orphan*/  es_pvid; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_2__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  stub1 (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8327_port_vlan_setup(struct arswitch_softc *sc, etherswitch_port_t *p)
{

	/* Check: ADDTAG/STRIPTAG - exclusive */

	ARSWITCH_LOCK(sc);

	/* Set the PVID. */
	if (p->es_pvid != 0)
		sc->hal.arswitch_vlan_set_pvid(sc, p->es_port, p->es_pvid);

	/*
	 * DOUBLE_TAG
	 * VLAN_MODE_ADD
	 * VLAN_MODE_STRIP
	 */
	ARSWITCH_UNLOCK(sc);
	return (0);
}