#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_journal_softc {int sc_bio_flush; TYPE_2__* sc_dconsumer; TYPE_2__* sc_jconsumer; } ;
struct bintime {int dummy; } ;
struct TYPE_4__ {TYPE_1__* provider; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int GJ_FLUSH_DATA ; 
 int GJ_FLUSH_JOURNAL ; 
 int /*<<< orphan*/  GJ_TIMER_START (int,struct bintime*) ; 
 int /*<<< orphan*/  GJ_TIMER_STOP (int,struct bintime*,char*) ; 
 int g_io_flush (TYPE_2__*) ; 

__attribute__((used)) static void
g_journal_flush_cache(struct g_journal_softc *sc)
{
	struct bintime bt;
	int error;

	if (sc->sc_bio_flush == 0)
		return;
	GJ_TIMER_START(1, &bt);
	if (sc->sc_bio_flush & GJ_FLUSH_JOURNAL) {
		error = g_io_flush(sc->sc_jconsumer);
		GJ_DEBUG(error == 0 ? 2 : 0, "Flush cache of %s: error=%d.",
		    sc->sc_jconsumer->provider->name, error);
	}
	if (sc->sc_bio_flush & GJ_FLUSH_DATA) {
		/*
		 * TODO: This could be called in parallel with the
		 *       previous call.
		 */
		error = g_io_flush(sc->sc_dconsumer);
		GJ_DEBUG(error == 0 ? 2 : 0, "Flush cache of %s: error=%d.",
		    sc->sc_dconsumer->provider->name, error);
	}
	GJ_TIMER_STOP(1, &bt, "Cache flush time");
}