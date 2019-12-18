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
struct tsec_softc {TYPE_1__* tsec_ifp; } ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int TSEC_IEVENT_TXB ; 
 int TSEC_IEVENT_TXF ; 
 int /*<<< orphan*/  TSEC_REG_IEVENT ; 
 int /*<<< orphan*/  TSEC_TRANSMIT_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_TRANSMIT_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsec_transmit_intr_locked (struct tsec_softc*) ; 

void
tsec_transmit_intr(void *arg)
{
	struct tsec_softc *sc = arg;

	TSEC_TRANSMIT_LOCK(sc);

#ifdef DEVICE_POLLING
	if (sc->tsec_ifp->if_capenable & IFCAP_POLLING) {
		TSEC_TRANSMIT_UNLOCK(sc);
		return;
	}
#endif
	/* Confirm the interrupt was received by driver */
	TSEC_WRITE(sc, TSEC_REG_IEVENT, TSEC_IEVENT_TXB | TSEC_IEVENT_TXF);
	tsec_transmit_intr_locked(sc);

	TSEC_TRANSMIT_UNLOCK(sc);
}