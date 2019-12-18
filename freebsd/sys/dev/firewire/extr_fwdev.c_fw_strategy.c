#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cdev {int dummy; } ;
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; struct cdev* bio_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ DEV_FWMEM (struct cdev*) ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  fwmem_strategy (struct bio*) ; 

__attribute__((used)) static void
fw_strategy(struct bio *bp)
{
	struct cdev *dev;

	dev = bp->bio_dev;
	if (DEV_FWMEM(dev)) {
		fwmem_strategy(bp);
		return;
	}

	bp->bio_error = EOPNOTSUPP;
	bp->bio_flags |= BIO_ERROR;
	bp->bio_resid = bp->bio_bcount;
	biodone(bp);
}