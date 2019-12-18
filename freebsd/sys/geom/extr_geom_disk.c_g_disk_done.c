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
struct g_disk_softc {int /*<<< orphan*/  done_mtx; TYPE_2__* dp; } ;
struct bio {scalar_t__ bio_error; int bio_cmd; scalar_t__ bio_inbed; scalar_t__ bio_children; scalar_t__ bio_completed; scalar_t__ bio_bcount; scalar_t__ bio_resid; int /*<<< orphan*/  bio_zone; scalar_t__ bio_length; TYPE_1__* bio_to; struct bio* bio_parent; } ;
struct bintime {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_devstat; } ;
struct TYPE_3__ {struct g_disk_softc* private; } ;

/* Variables and functions */
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_READ 130 
#define  BIO_WRITE 129 
#define  BIO_ZONE 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 
 int /*<<< orphan*/  devstat_end_transaction_bio_bt (int /*<<< orphan*/ ,struct bio*,struct bintime*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_disk_done(struct bio *bp)
{
	struct bintime now;
	struct bio *bp2;
	struct g_disk_softc *sc;

	/* See "notes" for why we need a mutex here */
	/* XXX: will witness accept a mix of Giant/unGiant drivers here ? */
	bp2 = bp->bio_parent;
	sc = bp2->bio_to->private;
	bp->bio_completed = bp->bio_length - bp->bio_resid;
	binuptime(&now);
	mtx_lock(&sc->done_mtx);
	if (bp2->bio_error == 0)
		bp2->bio_error = bp->bio_error;
	bp2->bio_completed += bp->bio_completed;

	switch (bp->bio_cmd) {
	case BIO_ZONE:
		bcopy(&bp->bio_zone, &bp2->bio_zone, sizeof(bp->bio_zone));
		/*FALLTHROUGH*/
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
	case BIO_FLUSH:
		devstat_end_transaction_bio_bt(sc->dp->d_devstat, bp, &now);
		break;
	default:
		break;
	}
	bp2->bio_inbed++;
	if (bp2->bio_children == bp2->bio_inbed) {
		mtx_unlock(&sc->done_mtx);
		bp2->bio_resid = bp2->bio_bcount - bp2->bio_completed;
		g_io_deliver(bp2, bp2->bio_error);
	} else
		mtx_unlock(&sc->done_mtx);
	g_destroy_bio(bp);
}