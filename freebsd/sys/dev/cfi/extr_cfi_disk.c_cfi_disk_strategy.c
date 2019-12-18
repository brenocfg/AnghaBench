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
struct cfi_disk_softc {int /*<<< orphan*/  iotask; int /*<<< orphan*/  tq; int /*<<< orphan*/  qlock; int /*<<< orphan*/  bioq; } ;
struct bio {scalar_t__ bio_bcount; scalar_t__ bio_resid; int bio_cmd; int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_flags; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct cfi_disk_softc* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfi_disk_strategy(struct bio *bp)
{
	struct cfi_disk_softc *sc = bp->bio_disk->d_drv1;

	if (sc == NULL)
		goto invalid;
	if (bp->bio_bcount == 0) {
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
		return;
	}
	switch (bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
		mtx_lock(&sc->qlock);
		/* no value in sorting requests? */
		bioq_insert_tail(&sc->bioq, bp);
		mtx_unlock(&sc->qlock);
		taskqueue_enqueue(sc->tq, &sc->iotask);
		return;
	}
	/* fall thru... */
invalid:
	bp->bio_flags |= BIO_ERROR;
	bp->bio_error = EINVAL;
	biodone(bp);
}