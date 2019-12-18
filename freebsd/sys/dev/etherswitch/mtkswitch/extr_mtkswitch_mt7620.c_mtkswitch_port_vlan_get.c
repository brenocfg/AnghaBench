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
struct TYPE_4__ {int /*<<< orphan*/  (* mtkswitch_vlan_get_pvid ) (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;
struct TYPE_5__ {scalar_t__ es_flags; int /*<<< orphan*/  es_pvid; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_2__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtkswitch_port_vlan_get(struct mtkswitch_softc *sc, etherswitch_port_t *p)
{

	MTKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);
	MTKSWITCH_LOCK(sc);

	/* Retrieve the PVID */
	sc->hal.mtkswitch_vlan_get_pvid(sc, p->es_port, &p->es_pvid);

	/*
	 * Port flags are not supported at the moment.
	 * Port's tag/untag/stack behaviour is defined per-VLAN.
	 */
	p->es_flags = 0;

	MTKSWITCH_UNLOCK(sc);

	return (0);
}