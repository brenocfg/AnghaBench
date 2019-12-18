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
struct cdevsw {TYPE_1__* d_gianttrick; } ;
struct cdev {int dummy; } ;
struct bio {struct cdev* bio_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* d_strategy ) (struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cdevsw* dev_refthread (struct cdev*,int*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 

__attribute__((used)) static void
giant_strategy(struct bio *bp)
{
	struct cdevsw *dsw;
	struct cdev *dev;
	int ref;

	dev = bp->bio_dev;
	dsw = dev_refthread(dev, &ref);
	if (dsw == NULL) {
		biofinish(bp, NULL, ENXIO);
		return;
	}
	mtx_lock(&Giant);
	dsw->d_gianttrick->d_strategy(bp);
	mtx_unlock(&Giant);
	dev_relthread(dev, ref);
}