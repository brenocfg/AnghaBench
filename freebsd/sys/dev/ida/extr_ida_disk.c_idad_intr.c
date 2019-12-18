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
struct idad_softc {int dummy; } ;
struct bio {int bio_flags; scalar_t__ bio_resid; int /*<<< orphan*/  bio_error; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct idad_softc* d_drv1; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 

void
idad_intr(struct bio *bp)
{
	struct idad_softc *drv;

	drv = bp->bio_disk->d_drv1;

	if (bp->bio_flags & BIO_ERROR)
		bp->bio_error = EIO;
	else
		bp->bio_resid = 0;

	biodone(bp);
}