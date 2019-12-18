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
typedef  int /*<<< orphan*/  uint32_t ;
struct mge_softc {TYPE_1__* ifp; } ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE_EXT ; 
 int /*<<< orphan*/  MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_RECEIVE_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_RECEIVE_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_intr_rx_check (struct mge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mge_intr_rx(void *arg) {
	struct mge_softc *sc;
	uint32_t int_cause, int_cause_ext;

	sc = arg;
	MGE_RECEIVE_LOCK(sc);

#ifdef DEVICE_POLLING
	if (sc->ifp->if_capenable & IFCAP_POLLING) {
		MGE_RECEIVE_UNLOCK(sc);
		return;
	}
#endif

	/* Get interrupt cause */
	int_cause = MGE_READ(sc, MGE_PORT_INT_CAUSE);
	int_cause_ext = MGE_READ(sc, MGE_PORT_INT_CAUSE_EXT);

	mge_intr_rx_check(sc, int_cause, int_cause_ext);

	MGE_RECEIVE_UNLOCK(sc);
}