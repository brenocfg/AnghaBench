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
typedef  scalar_t__ time_t ;
struct ncr53c9x_tinfo {int /*<<< orphan*/  luns; int /*<<< orphan*/ ** lun; } ;
struct ncr53c9x_softc {int sc_ntarg; int /*<<< orphan*/  sc_watchdog; struct ncr53c9x_tinfo* sc_tinfo; } ;
struct ncr53c9x_linfo {scalar_t__ last_used; scalar_t__ used; size_t lun; int /*<<< orphan*/ * untagged; } ;

/* Variables and functions */
 struct ncr53c9x_linfo* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct ncr53c9x_linfo* LIST_NEXT (struct ncr53c9x_linfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ncr53c9x_linfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 size_t NCR_NLUN ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  free (struct ncr53c9x_linfo*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ time_second ; 

__attribute__((used)) static void
ncr53c9x_watch(void *arg)
{
	struct ncr53c9x_softc *sc = arg;
	struct ncr53c9x_linfo *li;
	struct ncr53c9x_tinfo *ti;
	time_t old;
	int t;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	/* Delete any structures that have not been used in 10min. */
	old = time_second - (10 * 60);

	for (t = 0; t < sc->sc_ntarg; t++) {
		ti = &sc->sc_tinfo[t];
		li = LIST_FIRST(&ti->luns);
		while (li) {
			if (li->last_used < old &&
			    li->untagged == NULL &&
			    li->used == 0) {
				if (li->lun < NCR_NLUN)
					ti->lun[li->lun] = NULL;
				LIST_REMOVE(li, link);
				free(li, M_DEVBUF);
				/* Restart the search at the beginning. */
				li = LIST_FIRST(&ti->luns);
				continue;
			}
			li = LIST_NEXT(li, link);
		}
	}
	callout_reset(&sc->sc_watchdog, 60 * hz, ncr53c9x_watch, sc);
}