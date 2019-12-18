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
struct sfxge_softc {unsigned int evq_count; int /*<<< orphan*/ * ev_stats; struct sfxge_evq** evq; scalar_t__ ev_stats_update_time; } ;
struct sfxge_evq {scalar_t__* stats; } ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 unsigned int EV_NQSTATS ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_UNLOCK (struct sfxge_softc*) ; 
 scalar_t__ hz ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfxge_evq_stat_update (struct sfxge_evq*) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
sfxge_ev_stat_update(struct sfxge_softc *sc)
{
	struct sfxge_evq *evq;
	unsigned int index;
	clock_t now;
	unsigned int id;

	SFXGE_ADAPTER_LOCK(sc);

	now = ticks;
	if ((unsigned int)(now - sc->ev_stats_update_time) < (unsigned int)hz)
		goto out;

	sc->ev_stats_update_time = now;

	memset(sc->ev_stats, 0, sizeof(sc->ev_stats));

	/* Update and add event counts from each event queue in turn */
	for (index = 0; index < sc->evq_count; index++) {
		evq = sc->evq[index];
		sfxge_evq_stat_update(evq);
		for (id = 0; id < EV_NQSTATS; id++)
			sc->ev_stats[id] += evq->stats[id];
	}
out:
	SFXGE_ADAPTER_UNLOCK(sc);
}