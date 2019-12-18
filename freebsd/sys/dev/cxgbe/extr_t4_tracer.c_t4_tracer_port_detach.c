#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adapter {int /*<<< orphan*/  media; int /*<<< orphan*/  ifp_lock; TYPE_1__* ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_trace_lock ; 

void
t4_tracer_port_detach(struct adapter *sc)
{

	sx_xlock(&t4_trace_lock);
	if (sc->ifp != NULL) {
		mtx_lock(&sc->ifp_lock);
		sc->ifp->if_softc = NULL;
		sc->ifp = NULL;
		mtx_unlock(&sc->ifp_lock);
	}
	ifmedia_removeall(&sc->media);
	sx_xunlock(&t4_trace_lock);
}