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
struct nvd_disk {scalar_t__ cur_depth; int /*<<< orphan*/  bioqlock; int /*<<< orphan*/  bioq; } ;
struct bio {int bio_flags; } ;

/* Variables and functions */
 int BIO_ORDERED ; 
 scalar_t__ NVD_ODEPTH ; 
 scalar_t__ __predict_false (int) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvd_bio_submit (struct nvd_disk*,struct bio*) ; 
 int /*<<< orphan*/  tsleep (scalar_t__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
nvd_bioq_process(void *arg, int pending)
{
	struct nvd_disk *ndisk = arg;
	struct bio *bp;

	for (;;) {
		mtx_lock(&ndisk->bioqlock);
		bp = bioq_takefirst(&ndisk->bioq);
		mtx_unlock(&ndisk->bioqlock);
		if (bp == NULL)
			break;

		if (__predict_false(bp->bio_flags & BIO_ORDERED)) {
			/*
			 * bio with BIO_ORDERED flag set must be executed
			 * after all previous bios.
			 */
			while (ndisk->cur_depth > 0)
				tsleep(&ndisk->cur_depth, 0, "nvdorb", 1);
		} else {
			/*
			 * bio with BIO_ORDERED flag set must be completed
			 * before proceeding with additional bios.
			 */
			while (ndisk->cur_depth >= NVD_ODEPTH)
				tsleep(&ndisk->cur_depth, 0, "nvdora", 1);
		}

		nvd_bio_submit(ndisk, bp);
	}
}