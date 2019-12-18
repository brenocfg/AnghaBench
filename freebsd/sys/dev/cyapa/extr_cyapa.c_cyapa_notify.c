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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct cyapa_softc {TYPE_1__ selinfo; scalar_t__ isselect; scalar_t__ blocked; int /*<<< orphan*/  rfifo; scalar_t__ data_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_LOCK_ASSERT (struct cyapa_softc*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_empty (struct cyapa_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
cyapa_notify(struct cyapa_softc *sc)
{

	CYAPA_LOCK_ASSERT(sc);

	if (sc->data_signal || !fifo_empty(sc, &sc->rfifo)) {
		KNOTE_LOCKED(&sc->selinfo.si_note, 0);
		if (sc->blocked || sc->isselect) {
			if (sc->blocked) {
			    sc->blocked = 0;
			    wakeup(&sc->blocked);
			}
			if (sc->isselect) {
			    sc->isselect = 0;
			    selwakeup(&sc->selinfo);
			}
		}
	}
}