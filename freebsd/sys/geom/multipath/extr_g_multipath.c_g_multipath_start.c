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
struct g_multipath_softc {uintptr_t sc_ndisks; int /*<<< orphan*/  sc_mtx; } ;
struct g_geom {struct g_multipath_softc* softc; } ;
struct g_consumer {int /*<<< orphan*/  private; } ;
struct bio {int /*<<< orphan*/  bio_done; void* bio_driver1; TYPE_1__* bio_to; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 struct g_consumer* g_multipath_choose (struct g_geom*,struct bio*) ; 
 int /*<<< orphan*/  g_multipath_done ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_multipath_start(struct bio *bp)
{
	struct g_multipath_softc *sc;
	struct g_geom *gp;
	struct g_consumer *cp;
	struct bio *cbp;
	uintptr_t *cnt;

	gp = bp->bio_to->geom;
	sc = gp->softc;
	KASSERT(sc != NULL, ("NULL sc"));
	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}
	mtx_lock(&sc->sc_mtx);
	cp = g_multipath_choose(gp, bp);
	if (cp == NULL) {
		mtx_unlock(&sc->sc_mtx);
		g_destroy_bio(cbp);
		g_io_deliver(bp, ENXIO);
		return;
	}
	if ((uintptr_t)bp->bio_driver1 < sc->sc_ndisks)
		bp->bio_driver1 = (void *)(uintptr_t)sc->sc_ndisks;
	cnt = (uintptr_t *)&cp->private;
	(*cnt)++;
	mtx_unlock(&sc->sc_mtx);
	cbp->bio_done = g_multipath_done;
	g_io_request(cbp, cp);
}