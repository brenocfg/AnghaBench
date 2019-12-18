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
typedef  int uint32_t ;
struct mge_softc {TYPE_1__* ifp; } ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE_EXT ; 
 int MGE_PORT_INT_EXT_TXBUF0 ; 
 int MGE_PORT_INT_EXT_TXUR ; 
 int MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_TRANSMIT_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_TRANSMIT_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mge_intr_tx_locked (struct mge_softc*) ; 

__attribute__((used)) static void
mge_intr_tx(void *arg)
{
	struct mge_softc *sc = arg;
	uint32_t int_cause_ext;

	MGE_TRANSMIT_LOCK(sc);

#ifdef DEVICE_POLLING
	if (sc->ifp->if_capenable & IFCAP_POLLING) {
		MGE_TRANSMIT_UNLOCK(sc);
		return;
	}
#endif

	/* Ack the interrupt */
	int_cause_ext = MGE_READ(sc, MGE_PORT_INT_CAUSE_EXT);
	MGE_WRITE(sc, MGE_PORT_INT_CAUSE_EXT, ~(int_cause_ext &
	    (MGE_PORT_INT_EXT_TXBUF0 | MGE_PORT_INT_EXT_TXUR)));

	mge_intr_tx_locked(sc);

	MGE_TRANSMIT_UNLOCK(sc);
}