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
struct g_raid_softc {int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; } ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_attribute; TYPE_2__* bio_to; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_raid_softc* softc; } ;

/* Variables and functions */
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,struct g_raid_softc*) ; 
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  dumping ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_candelete (struct g_raid_softc*,struct bio*) ; 
 int /*<<< orphan*/  g_raid_kerneldump (struct g_raid_softc*,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wakeup (struct g_raid_softc*) ; 

__attribute__((used)) static void
g_raid_start(struct bio *bp)
{
	struct g_raid_softc *sc;

	sc = bp->bio_to->geom->softc;
	/*
	 * If sc == NULL or there are no valid disks, provider's error
	 * should be set and g_raid_start() should not be called at all.
	 */
//	KASSERT(sc != NULL && sc->sc_state == G_RAID_VOLUME_S_RUNNING,
//	    ("Provider's error should be set (error=%d)(mirror=%s).",
//	    bp->bio_to->error, bp->bio_to->name));
	G_RAID_LOGREQ(3, bp, "Request received.");

	switch (bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
	case BIO_FLUSH:
		break;
	case BIO_GETATTR:
		if (!strcmp(bp->bio_attribute, "GEOM::candelete"))
			g_raid_candelete(sc, bp);
		else if (!strcmp(bp->bio_attribute, "GEOM::kerneldump"))
			g_raid_kerneldump(sc, bp);
		else
			g_io_deliver(bp, EOPNOTSUPP);
		return;
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		return;
	}
	mtx_lock(&sc->sc_queue_mtx);
	bioq_insert_tail(&sc->sc_queue, bp);
	mtx_unlock(&sc->sc_queue_mtx);
	if (!dumping) {
		G_RAID_DEBUG1(4, sc, "Waking up %p.", sc);
		wakeup(sc);
	}
}