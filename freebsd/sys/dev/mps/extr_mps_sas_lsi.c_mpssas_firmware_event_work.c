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
struct mps_softc {TYPE_1__* sassc; } ;
struct mps_fw_event_work {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev_queue; } ;

/* Variables and functions */
 struct mps_fw_event_work* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mps_fw_event_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  mps_lock (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_unlock (struct mps_softc*) ; 
 int /*<<< orphan*/  mpssas_fw_work (struct mps_softc*,struct mps_fw_event_work*) ; 

void
mpssas_firmware_event_work(void *arg, int pending)
{
	struct mps_fw_event_work *fw_event;
	struct mps_softc *sc;

	sc = (struct mps_softc *)arg;
	mps_lock(sc);
	while ((fw_event = TAILQ_FIRST(&sc->sassc->ev_queue)) != NULL) {
		TAILQ_REMOVE(&sc->sassc->ev_queue, fw_event, ev_link);
		mpssas_fw_work(sc, fw_event);
	}
	mps_unlock(sc);
}