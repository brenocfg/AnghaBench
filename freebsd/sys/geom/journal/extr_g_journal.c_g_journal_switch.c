#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_provider {scalar_t__ acw; scalar_t__ sectorsize; } ;
struct TYPE_6__ {int /*<<< orphan*/ * jj_queue; scalar_t__ jj_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/ * jj_queue; scalar_t__ jj_offset; } ;
struct g_journal_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; TYPE_3__ sc_active; scalar_t__ sc_journal_offset; TYPE_2__ sc_inactive; int /*<<< orphan*/  sc_journal_next_id; int /*<<< orphan*/  sc_journal_id; int /*<<< orphan*/  sc_journal_previous_id; struct g_provider* sc_jprovider; TYPE_1__* sc_geom; int /*<<< orphan*/  sc_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  provider; } ;

/* Variables and functions */
 int GJF_DEVICE_CLEAN ; 
 int GJF_DEVICE_SWITCH ; 
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GJ_VALIDATE_OFFSET (scalar_t__,struct g_journal_softc*) ; 
 scalar_t__ JEMPTY (struct g_journal_softc*) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  g_journal_copy_start (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_metadata_update (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_write_header (struct g_journal_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_journal_switch(struct g_journal_softc *sc)
{
	struct g_provider *pp;

	if (JEMPTY(sc)) {
		GJ_DEBUG(3, "No need for %s switch.", sc->sc_name);
		pp = LIST_FIRST(&sc->sc_geom->provider);
		if (!(sc->sc_flags & GJF_DEVICE_CLEAN) && pp->acw == 0) {
			sc->sc_flags |= GJF_DEVICE_CLEAN;
			GJ_DEBUG(1, "Marking %s as clean.", sc->sc_name);
			g_journal_metadata_update(sc);
		}
	} else {
		GJ_DEBUG(3, "Switching journal %s.", sc->sc_geom->name);

		pp = sc->sc_jprovider;

		sc->sc_journal_previous_id = sc->sc_journal_id;

		sc->sc_journal_id = sc->sc_journal_next_id;
		sc->sc_journal_next_id = arc4random();

		GJ_VALIDATE_OFFSET(sc->sc_journal_offset, sc);

		g_journal_write_header(sc);

		sc->sc_inactive.jj_offset = sc->sc_active.jj_offset;
		sc->sc_inactive.jj_queue = sc->sc_active.jj_queue;

		sc->sc_active.jj_offset =
		    sc->sc_journal_offset - pp->sectorsize;
		sc->sc_active.jj_queue = NULL;

		/*
		 * Switch is done, start copying data from the (now) inactive
		 * journal to the data provider.
		 */
		g_journal_copy_start(sc);
	}
	mtx_lock(&sc->sc_mtx);
	sc->sc_flags &= ~GJF_DEVICE_SWITCH;
	mtx_unlock(&sc->sc_mtx);
}