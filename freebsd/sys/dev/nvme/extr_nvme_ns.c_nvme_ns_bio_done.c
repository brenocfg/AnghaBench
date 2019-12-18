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
struct nvme_completion {int dummy; } ;
struct bio {int bio_flags; scalar_t__ bio_error; scalar_t__ bio_bcount; scalar_t__ bio_resid; scalar_t__ bio_driver2; int /*<<< orphan*/  (* bio_driver1 ) (struct bio*,struct nvme_completion const*) ;} ;
typedef  int /*<<< orphan*/  (* nvme_cb_fn_t ) (struct bio*,struct nvme_completion const*) ;

/* Variables and functions */
 int BIO_ERROR ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  M_NVME ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_completion_is_error (struct nvme_completion const*) ; 

__attribute__((used)) static void
nvme_ns_bio_done(void *arg, const struct nvme_completion *status)
{
	struct bio	*bp = arg;
	nvme_cb_fn_t	bp_cb_fn;

	bp_cb_fn = bp->bio_driver1;

	if (bp->bio_driver2)
		free(bp->bio_driver2, M_NVME);

	if (nvme_completion_is_error(status)) {
		bp->bio_flags |= BIO_ERROR;
		if (bp->bio_error == 0)
			bp->bio_error = EIO;
	}

	if ((bp->bio_flags & BIO_ERROR) == 0)
		bp->bio_resid = 0;
	else
		bp->bio_resid = bp->bio_bcount;

	bp_cb_fn(bp, status);
}