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
struct twed_softc {int /*<<< orphan*/  twed_controller; TYPE_1__* twed_drive; } ;
struct bio {int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; int /*<<< orphan*/ * bio_driver1; TYPE_2__* bio_disk; } ;
struct TYPE_4__ {struct twed_softc* d_drv1; } ;
struct TYPE_3__ {int /*<<< orphan*/ * td_disk; int /*<<< orphan*/  td_twe_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  TWED_BIO_IN ; 
 int /*<<< orphan*/  TWED_BIO_OUT ; 
 int /*<<< orphan*/  TWE_IO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  twe_enqueue_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  twe_startio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
twed_strategy(struct bio *bp)
{
    struct twed_softc	*sc = bp->bio_disk->d_drv1;

    debug_called(4);

    bp->bio_driver1 = &sc->twed_drive->td_twe_unit;
    TWED_BIO_IN;

    /* bogus disk? */
    if (sc == NULL || sc->twed_drive->td_disk == NULL) {
	bp->bio_error = EINVAL;
	bp->bio_flags |= BIO_ERROR;
	printf("twe: bio for invalid disk!\n");
	biodone(bp);
	TWED_BIO_OUT;
	return;
    }

    /* queue the bio on the controller */
    TWE_IO_LOCK(sc->twed_controller);
    twe_enqueue_bio(sc->twed_controller, bp);

    /* poke the controller to start I/O */
    twe_startio(sc->twed_controller);
    TWE_IO_UNLOCK(sc->twed_controller);
    return;
}