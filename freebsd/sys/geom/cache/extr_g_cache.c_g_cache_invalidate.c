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
struct g_cache_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_invalid; int /*<<< orphan*/  sc_nused; int /*<<< orphan*/  sc_usedlist; } ;
struct g_cache_desc {int d_flags; int /*<<< orphan*/ * d_biolist; } ;
struct bio {scalar_t__ bio_length; scalar_t__ bio_offset; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int D_FLAG_INVALID ; 
 int D_FLAG_USED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ OFF2BNO (scalar_t__,struct g_cache_softc*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  d_used ; 
 int /*<<< orphan*/  g_cache_free (struct g_cache_softc*,struct g_cache_desc*) ; 
 struct g_cache_desc* g_cache_lookup (struct g_cache_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_cache_invalidate(struct g_cache_softc *sc, struct bio *bp)
{
	struct g_cache_desc *dp;
	off_t bno, lim;

	mtx_lock(&sc->sc_mtx);
	bno = OFF2BNO(bp->bio_offset, sc);
	lim = OFF2BNO(bp->bio_offset + bp->bio_length - 1, sc);
	do {
		if ((dp = g_cache_lookup(sc, bno)) != NULL) {
			LIST_REMOVE(dp, d_next);
			if (dp->d_flags & D_FLAG_USED) {
				TAILQ_REMOVE(&sc->sc_usedlist, dp, d_used);
				sc->sc_nused--;
			}
			if (dp->d_biolist == NULL)
				g_cache_free(sc, dp);
			else {
				dp->d_flags = D_FLAG_INVALID;
				sc->sc_invalid++;
			}
		}
		bno++;
	} while (bno <= lim);
	mtx_unlock(&sc->sc_mtx);
}