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
struct mfi_system_pd {scalar_t__ pd_id; struct mfi_softc* pd_controller; } ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; } ;
struct bio {void* bio_driver2; void* bio_driver1; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct mfi_system_pd* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MFI_SYS_PD_IO ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  mfi_enqueue_bio (struct mfi_softc*,struct bio*) ; 
 int /*<<< orphan*/  mfi_startio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfi_syspd_strategy(struct bio *bio)
{
	struct mfi_system_pd *sc;
	struct mfi_softc *controller;

	sc = bio->bio_disk->d_drv1;

	if (sc == NULL) {
		bio->bio_error = EINVAL;
		bio->bio_flags |= BIO_ERROR;
		bio->bio_resid = bio->bio_bcount;
		biodone(bio);
		return;
	}

	controller = sc->pd_controller;
	bio->bio_driver1 = (void *)(uintptr_t)sc->pd_id;
	/* Mark it as system PD IO */
	bio->bio_driver2 = (void *)MFI_SYS_PD_IO;
	mtx_lock(&controller->mfi_io_lock);
	mfi_enqueue_bio(controller, bio);
	mfi_startio(controller);
	mtx_unlock(&controller->mfi_io_lock);
	return;
}