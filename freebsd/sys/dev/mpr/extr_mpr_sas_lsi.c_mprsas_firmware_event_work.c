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
struct mpr_softc {TYPE_1__* sassc; } ;
struct mpr_fw_event_work {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev_queue; } ;

/* Variables and functions */
 struct mpr_fw_event_work* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mpr_fw_event_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  mpr_lock (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_unlock (struct mpr_softc*) ; 
 int /*<<< orphan*/  mprsas_fw_work (struct mpr_softc*,struct mpr_fw_event_work*) ; 

void
mprsas_firmware_event_work(void *arg, int pending)
{
	struct mpr_fw_event_work *fw_event;
	struct mpr_softc *sc;

	sc = (struct mpr_softc *)arg;
	mpr_lock(sc);
	while ((fw_event = TAILQ_FIRST(&sc->sassc->ev_queue)) != NULL) {
		TAILQ_REMOVE(&sc->sassc->ev_queue, fw_event, ev_link);
		mprsas_fw_work(sc, fw_event);
	}
	mpr_unlock(sc);
}