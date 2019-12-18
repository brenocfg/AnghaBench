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
struct g_geom {int /*<<< orphan*/  consumer; struct g_cache_softc* softc; } ;
struct g_cache_softc {scalar_t__ sc_wrotebytes; int /*<<< orphan*/  sc_writes; scalar_t__ sc_cachereadbytes; int /*<<< orphan*/  sc_cachereads; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_tail; scalar_t__ sc_readbytes; int /*<<< orphan*/  sc_reads; } ;
struct g_cache_desc {int /*<<< orphan*/ * d_biolist; } ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_done; scalar_t__ bio_length; scalar_t__ bio_offset; TYPE_1__* bio_to; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  G_CACHE_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OFF2BNO (scalar_t__,struct g_cache_softc*) ; 
 int /*<<< orphan*/  g_cache_deliver (struct g_cache_softc*,struct bio*,struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cache_enable ; 
 int /*<<< orphan*/  g_cache_invalidate (struct g_cache_softc*,struct bio*) ; 
 struct g_cache_desc* g_cache_lookup (struct g_cache_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cache_read (struct g_cache_softc*,struct bio*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_std_done ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_cache_start(struct bio *bp)
{
	struct g_cache_softc *sc;
	struct g_geom *gp;
	struct g_cache_desc *dp;
	struct bio *cbp;

	gp = bp->bio_to->geom;
	sc = gp->softc;
	G_CACHE_LOGREQ(bp, "Request received.");
	switch (bp->bio_cmd) {
	case BIO_READ:
		sc->sc_reads++;
		sc->sc_readbytes += bp->bio_length;
		if (!g_cache_enable)
			break;
		if (bp->bio_offset + bp->bio_length > sc->sc_tail)
			break;
		if (OFF2BNO(bp->bio_offset, sc) ==
		    OFF2BNO(bp->bio_offset + bp->bio_length - 1, sc)) {
			sc->sc_cachereads++;
			sc->sc_cachereadbytes += bp->bio_length;
			if (g_cache_read(sc, bp) == 0)
				return;
			sc->sc_cachereads--;
			sc->sc_cachereadbytes -= bp->bio_length;
			break;
		} else if (OFF2BNO(bp->bio_offset, sc) + 1 ==
		    OFF2BNO(bp->bio_offset + bp->bio_length - 1, sc)) {
			mtx_lock(&sc->sc_mtx);
			dp = g_cache_lookup(sc, OFF2BNO(bp->bio_offset, sc));
			if (dp == NULL || dp->d_biolist != NULL) {
				mtx_unlock(&sc->sc_mtx);
				break;
			}
			sc->sc_cachereads++;
			sc->sc_cachereadbytes += bp->bio_length;
			g_cache_deliver(sc, bp, dp, 0);
			mtx_unlock(&sc->sc_mtx);
			if (g_cache_read(sc, bp) == 0)
				return;
			sc->sc_cachereads--;
			sc->sc_cachereadbytes -= bp->bio_length;
			break;
		}
		break;
	case BIO_WRITE:
		sc->sc_writes++;
		sc->sc_wrotebytes += bp->bio_length;
		g_cache_invalidate(sc, bp);
		break;
	}
	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}
	cbp->bio_done = g_std_done;
	G_CACHE_LOGREQ(cbp, "Sending request.");
	g_io_request(cbp, LIST_FIRST(&gp->consumer));
}