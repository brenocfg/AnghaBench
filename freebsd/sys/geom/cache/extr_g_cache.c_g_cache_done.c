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
struct g_cache_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_nused; int /*<<< orphan*/  sc_usedlist; int /*<<< orphan*/  sc_invalid; } ;
struct g_cache_desc {int d_flags; struct bio* d_biolist; } ;
struct bio {scalar_t__ bio_error; TYPE_2__* bio_from; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_cache_softc* softc; } ;

/* Variables and functions */
 int D_FLAG_INVALID ; 
 int D_FLAG_USED ; 
 struct g_cache_softc* G_CACHE_DESC1 (struct bio*) ; 
 struct g_cache_desc* G_CACHE_DESC2 (struct bio*) ; 
 struct g_cache_softc* G_CACHE_NEXT_BIO1 (struct bio*) ; 
 struct bio* G_CACHE_NEXT_BIO2 (struct bio*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  d_used ; 
 int /*<<< orphan*/  g_cache_deliver (struct g_cache_softc*,struct bio*,struct g_cache_desc*,scalar_t__) ; 
 int /*<<< orphan*/  g_cache_free (struct g_cache_softc*,struct g_cache_desc*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_cache_done(struct bio *bp)
{
	struct g_cache_softc *sc;
	struct g_cache_desc *dp;
	struct bio *bp2, *tmpbp;

	sc = bp->bio_from->geom->softc;
	KASSERT(G_CACHE_DESC1(bp) == sc, ("corrupt bio_caller in g_cache_done()"));
	dp = G_CACHE_DESC2(bp);
	mtx_lock(&sc->sc_mtx);
	bp2 = dp->d_biolist;
	while (bp2 != NULL) {
		KASSERT(G_CACHE_NEXT_BIO1(bp2) == sc, ("corrupt bio_driver in g_cache_done()"));
		tmpbp = G_CACHE_NEXT_BIO2(bp2);
		g_cache_deliver(sc, bp2, dp, bp->bio_error);
		bp2 = tmpbp;
	}
	dp->d_biolist = NULL;
	if (dp->d_flags & D_FLAG_INVALID) {
		sc->sc_invalid--;
		g_cache_free(sc, dp);
	} else if (bp->bio_error) {
		LIST_REMOVE(dp, d_next);
		if (dp->d_flags & D_FLAG_USED) {
			TAILQ_REMOVE(&sc->sc_usedlist, dp, d_used);
			sc->sc_nused--;
		}
		g_cache_free(sc, dp);
	}
	mtx_unlock(&sc->sc_mtx);
	g_destroy_bio(bp);
}