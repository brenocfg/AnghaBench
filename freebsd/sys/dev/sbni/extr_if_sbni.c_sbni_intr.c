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
struct sbni_softc {struct sbni_softc* slave_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int RC_RDY ; 
 int /*<<< orphan*/  SBNI_LOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  SBNI_UNLOCK (struct sbni_softc*) ; 
 int TR_RDY ; 
 int /*<<< orphan*/  handle_channel (struct sbni_softc*) ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 

void
sbni_intr(void *arg)
{
	struct sbni_softc *sc;
	int repeat;

	sc = (struct sbni_softc *)arg;

	do {
		repeat = 0;
		SBNI_LOCK(sc);
		if (sbni_inb(sc, CSR0) & (RC_RDY | TR_RDY)) {
			handle_channel(sc);
			repeat = 1;
		}
		SBNI_UNLOCK(sc);
		if (sc->slave_sc) {
			/* second channel present */
			SBNI_LOCK(sc->slave_sc);
			if (sbni_inb(sc->slave_sc, CSR0) & (RC_RDY | TR_RDY)) {
				handle_channel(sc->slave_sc);
				repeat = 1;
			}
			SBNI_UNLOCK(sc->slave_sc);
		}
	} while (repeat);
}