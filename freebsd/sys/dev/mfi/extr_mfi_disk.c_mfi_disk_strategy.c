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
struct mfi_softc {scalar_t__ issuepend_done; int /*<<< orphan*/  mfi_io_lock; scalar_t__ hw_crit_error; scalar_t__ adpreset; } ;
struct mfi_disk {scalar_t__ ld_id; struct mfi_softc* ld_controller; } ;
struct bio {void* bio_driver2; void* bio_driver1; void* bio_error; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct mfi_disk* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 void* EBUSY ; 
 void* EINVAL ; 
 scalar_t__ MFI_LD_IO ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  mfi_enqueue_bio (struct mfi_softc*,struct bio*) ; 
 int /*<<< orphan*/  mfi_startio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfi_disk_strategy(struct bio *bio)
{
	struct mfi_disk *sc;
	struct mfi_softc *controller;

	sc = bio->bio_disk->d_drv1;

	if (sc == NULL) {
		bio->bio_error = EINVAL;
		bio->bio_flags |= BIO_ERROR;
		bio->bio_resid = bio->bio_bcount;
		biodone(bio);
		return;
	}

	controller = sc->ld_controller;
	if (controller->adpreset) {
		bio->bio_error = EBUSY;
		return;
	}

	if (controller->hw_crit_error) {
		bio->bio_error = EBUSY;
		return;
	}

	if (controller->issuepend_done == 0) {
		bio->bio_error = EBUSY;
		return;
	}

	bio->bio_driver1 = (void *)(uintptr_t)sc->ld_id;
	/* Mark it as LD IO */
	bio->bio_driver2 = (void *)MFI_LD_IO;
	mtx_lock(&controller->mfi_io_lock);
	mfi_enqueue_bio(controller, bio);
	mfi_startio(controller);
	mtx_unlock(&controller->mfi_io_lock);
	return;
}