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
struct mmcsd_part {scalar_t__ running; scalar_t__ suspend; int /*<<< orphan*/  bio_queue; } ;
struct bio {TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct mmcsd_part* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  MMCSD_DISK_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_DISK_UNLOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  wakeup (struct mmcsd_part*) ; 

__attribute__((used)) static void
mmcsd_strategy(struct bio *bp)
{
	struct mmcsd_part *part;

	part = bp->bio_disk->d_drv1;
	MMCSD_DISK_LOCK(part);
	if (part->running > 0 || part->suspend > 0) {
		bioq_disksort(&part->bio_queue, bp);
		MMCSD_DISK_UNLOCK(part);
		wakeup(part);
	} else {
		MMCSD_DISK_UNLOCK(part);
		biofinish(bp, NULL, ENXIO);
	}
}