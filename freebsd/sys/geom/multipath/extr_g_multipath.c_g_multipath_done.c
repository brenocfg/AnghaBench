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
struct g_multipath_softc {int /*<<< orphan*/  sc_mtx; } ;
struct g_consumer {int index; int /*<<< orphan*/  private; TYPE_1__* geom; } ;
struct bio {scalar_t__ bio_error; struct g_consumer* bio_from; } ;
struct TYPE_2__ {struct g_multipath_softc* softc; } ;

/* Variables and functions */
 scalar_t__ EIO ; 
 scalar_t__ ENXIO ; 
 int MP_LOST ; 
 int MP_POSTED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_mpd ; 
 int /*<<< orphan*/  g_multipath_kt_state ; 
 scalar_t__ g_post_event (int /*<<< orphan*/ ,struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_std_done (struct bio*) ; 
 int /*<<< orphan*/  gmtbq ; 
 int /*<<< orphan*/  gmtbq_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_multipath_done(struct bio *bp)
{
	struct g_multipath_softc *sc;
	struct g_consumer *cp;
	uintptr_t *cnt;

	if (bp->bio_error == ENXIO || bp->bio_error == EIO) {
		mtx_lock(&gmtbq_mtx);
		bioq_insert_tail(&gmtbq, bp);
		mtx_unlock(&gmtbq_mtx);
		wakeup(&g_multipath_kt_state);
	} else {
		cp = bp->bio_from;
		sc = cp->geom->softc;
		cnt = (uintptr_t *)&cp->private;
		mtx_lock(&sc->sc_mtx);
		(*cnt)--;
		if (*cnt == 0 && (cp->index & MP_LOST)) {
			if (g_post_event(g_mpd, cp, M_NOWAIT, NULL) == 0)
				cp->index |= MP_POSTED;
			mtx_unlock(&sc->sc_mtx);
		} else
			mtx_unlock(&sc->sc_mtx);
		g_std_done(bp);
	}
}