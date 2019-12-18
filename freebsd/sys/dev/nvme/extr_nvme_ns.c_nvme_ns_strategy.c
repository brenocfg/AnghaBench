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
struct nvme_namespace {int dummy; } ;
struct bio {int bio_error; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; TYPE_1__* bio_dev; } ;
struct TYPE_2__ {struct nvme_namespace* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int nvme_ns_bio_process (struct nvme_namespace*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ns_strategy_done ; 

__attribute__((used)) static void
nvme_ns_strategy(struct bio *bp)
{
	struct nvme_namespace	*ns;
	int			err;

	ns = bp->bio_dev->si_drv1;
	err = nvme_ns_bio_process(ns, bp, nvme_ns_strategy_done);

	if (err) {
		bp->bio_error = err;
		bp->bio_flags |= BIO_ERROR;
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
	}

}