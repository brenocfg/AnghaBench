#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_flags; } ;
struct TYPE_3__ {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_softc {TYPE_1__ areq; int /*<<< orphan*/ * an_temp_keys; scalar_t__ mpi350; scalar_t__ an_gone; struct ifnet* an_ifp; } ;
struct an_ltv_key {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int /*<<< orphan*/  AN_RID_WEP_TEMP ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  an_init_locked (struct an_softc*) ; 
 int /*<<< orphan*/  an_init_mpi350_desc (struct an_softc*) ; 
 int /*<<< orphan*/  an_reset (struct an_softc*) ; 
 int /*<<< orphan*/  an_setdef (struct an_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  an_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

void
an_resume(device_t dev)
{
	struct an_softc		*sc;
	struct ifnet		*ifp;
	int			i;

	sc = device_get_softc(dev);
	AN_LOCK(sc);
	ifp = sc->an_ifp;

	sc->an_gone = 0;
	an_reset(sc);
	if (sc->mpi350)
		an_init_mpi350_desc(sc);
	an_init_locked(sc);

	/* Recovery temporary keys */
	for (i = 0; i < 4; i++) {
		sc->areq.an_type = AN_RID_WEP_TEMP;
		sc->areq.an_len = sizeof(struct an_ltv_key);
		bcopy(&sc->an_temp_keys[i],
		    &sc->areq, sizeof(struct an_ltv_key));
		an_setdef(sc, &sc->areq);
	}

	if (ifp->if_flags & IFF_UP)
		an_start_locked(ifp);
	AN_UNLOCK(sc);

	return;
}