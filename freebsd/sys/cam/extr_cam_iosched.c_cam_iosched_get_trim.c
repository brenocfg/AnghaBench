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
struct TYPE_4__ {int queued; } ;
struct TYPE_3__ {int queued; } ;
struct cam_iosched_softc {int current_read_bias; int read_bias; TYPE_2__ read_stats; TYPE_1__ trim_stats; int /*<<< orphan*/  bio_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_iosched_has_more_trim (struct cam_iosched_softc*) ; 
 struct bio* cam_iosched_next_trim (struct cam_iosched_softc*) ; 
 scalar_t__ do_dynamic_iosched ; 
 scalar_t__ iosched_debug ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

struct bio *
cam_iosched_get_trim(struct cam_iosched_softc *isc)
{

	if (!cam_iosched_has_more_trim(isc))
		return NULL;
#ifdef CAM_IOSCHED_DYNAMIC
	/*
	 * If pending read, prefer that based on current read bias setting. The
	 * read bias is shared for both writes and TRIMs, but on TRIMs the bias
	 * is for a combined TRIM not a single TRIM request that's come in.
	 */
	if (do_dynamic_iosched) {
		if (bioq_first(&isc->bio_queue) && isc->current_read_bias) {
			if (iosched_debug)
				printf("Reads present and current_read_bias is %d"
				    " queued trims %d queued reads %d\n",
				    isc->current_read_bias, isc->trim_stats.queued,
				    isc->read_stats.queued);
			isc->current_read_bias--;
			/* We're not limiting TRIMS, per se, just doing reads first */
			return NULL;
		}
		/*
		 * We're going to do a trim, so reset the bias.
		 */
		isc->current_read_bias = isc->read_bias;
	}
#endif
	return cam_iosched_next_trim(isc);
}