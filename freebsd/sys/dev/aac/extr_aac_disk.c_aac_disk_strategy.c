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
struct bio {scalar_t__ bio_bcount; scalar_t__ bio_resid; int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_flags; TYPE_2__* bio_disk; } ;
struct aac_disk {TYPE_1__* ad_controller; } ;
struct TYPE_4__ {scalar_t__ d_drv1; } ;
struct TYPE_3__ {int /*<<< orphan*/  aac_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_submit_bio (struct bio*) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aac_disk_strategy(struct bio *bp)
{
	struct aac_disk	*sc;

	sc = (struct aac_disk *)bp->bio_disk->d_drv1;
	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* bogus disk? */
	if (sc == NULL) {
		bp->bio_flags |= BIO_ERROR;
		bp->bio_error = EINVAL;
		biodone(bp);
		return;
	}

	/* do-nothing operation? */
	if (bp->bio_bcount == 0) {
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
		return;
	}

	/* perform accounting */

	/* pass the bio to the controller - it can work out who we are */
	mtx_lock(&sc->ad_controller->aac_io_lock);
	aac_submit_bio(bp);
	mtx_unlock(&sc->ad_controller->aac_io_lock);
}