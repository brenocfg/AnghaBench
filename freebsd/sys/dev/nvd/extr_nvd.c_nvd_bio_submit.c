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
struct nvd_disk {scalar_t__ cur_depth; scalar_t__ ordered_in_flight; int /*<<< orphan*/  ns; } ;
struct bio {int bio_flags; int bio_error; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/ * bio_driver1; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int BIO_ORDERED ; 
 int NVD_ODEPTH ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 
 int atomic_fetchadd_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  nvd_done ; 
 int nvme_ns_bio_process (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
nvd_bio_submit(struct nvd_disk *ndisk, struct bio *bp)
{
	int err;

	bp->bio_driver1 = NULL;
	if (__predict_false(bp->bio_flags & BIO_ORDERED))
		atomic_add_int(&ndisk->cur_depth, NVD_ODEPTH);
	else
		atomic_add_int(&ndisk->cur_depth, 1);
	err = nvme_ns_bio_process(ndisk->ns, bp, nvd_done);
	if (err) {
		if (__predict_false(bp->bio_flags & BIO_ORDERED)) {
			atomic_add_int(&ndisk->cur_depth, -NVD_ODEPTH);
			atomic_add_int(&ndisk->ordered_in_flight, -1);
			wakeup(&ndisk->cur_depth);
		} else {
			if (atomic_fetchadd_int(&ndisk->cur_depth, -1) == 1 &&
			    __predict_false(ndisk->ordered_in_flight != 0))
				wakeup(&ndisk->cur_depth);
		}
		bp->bio_error = err;
		bp->bio_flags |= BIO_ERROR;
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
	}
}