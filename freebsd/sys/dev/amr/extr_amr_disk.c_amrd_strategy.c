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
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; TYPE_1__* bio_disk; } ;
struct amrd_softc {int /*<<< orphan*/  amrd_controller; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  amr_submit_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 

__attribute__((used)) static void
amrd_strategy(struct bio *bio)
{
    struct amrd_softc	*sc = (struct amrd_softc *)bio->bio_disk->d_drv1;

    /* bogus disk? */
    if (sc == NULL) {
	bio->bio_error = EINVAL;
	goto bad;
    }

    amr_submit_bio(sc->amrd_controller, bio);
    return;

 bad:
    bio->bio_flags |= BIO_ERROR;

    /*
     * Correctly set the buf to indicate a completed transfer
     */
    bio->bio_resid = bio->bio_bcount;
    biodone(bio);
    return;
}