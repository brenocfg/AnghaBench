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
struct mmcsd_part {TYPE_2__* sc; } ;
struct bio {int bio_length; int bio_completed; int /*<<< orphan*/  bio_data; TYPE_1__* bio_disk; int /*<<< orphan*/  bio_attribute; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct mmcsd_part* d_drv1; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mmcsd_getattr(struct bio *bp)
{
	struct mmcsd_part *part;
	device_t dev;

	if (strcmp(bp->bio_attribute, "MMC::device") == 0) {
		if (bp->bio_length != sizeof(dev))
			return (EFAULT);
		part = bp->bio_disk->d_drv1;
		dev = part->sc->dev;
		bcopy(&dev, bp->bio_data, sizeof(dev));
		bp->bio_completed = bp->bio_length;
		return (0);
	}
	return (-1);
}