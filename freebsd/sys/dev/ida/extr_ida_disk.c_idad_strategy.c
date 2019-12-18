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
struct idad_softc {int flags; int /*<<< orphan*/  controller; } ;
struct bio {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; struct idad_softc* bio_driver1; int /*<<< orphan*/  bio_error; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct idad_softc* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_WRITE ; 
 int DRV_WRITEPROT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  ida_submit_buf (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static void
idad_strategy(struct bio *bp)
{
	struct idad_softc *drv;

	drv = bp->bio_disk->d_drv1;
	if (drv == NULL) {
    		bp->bio_error = EINVAL;
		goto bad;
	}

	/*
	 * software write protect check
	 */
	if (drv->flags & DRV_WRITEPROT && (bp->bio_cmd == BIO_WRITE)) {
		bp->bio_error = EROFS;
		goto bad;
	}

	bp->bio_driver1 = drv;
	ida_submit_buf(drv->controller, bp);
	return;

bad:
	bp->bio_flags |= BIO_ERROR;

	/*
	 * Correctly set the buf to indicate a completed transfer
	 */
	bp->bio_resid = bp->bio_bcount;
	biodone(bp);
	return;
}