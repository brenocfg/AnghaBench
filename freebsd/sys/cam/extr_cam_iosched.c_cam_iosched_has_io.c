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
struct TYPE_2__ {int pending; int max; int queued; } ;
struct cam_iosched_softc {int /*<<< orphan*/  bio_queue; TYPE_1__ write_stats; TYPE_1__ read_stats; int /*<<< orphan*/  write_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 scalar_t__ cam_iosched_limiter_caniop (TYPE_1__*,struct bio*) ; 
 scalar_t__ do_dynamic_iosched ; 
 int iosched_debug ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static inline bool
cam_iosched_has_io(struct cam_iosched_softc *isc)
{
#ifdef CAM_IOSCHED_DYNAMIC
	if (do_dynamic_iosched) {
		struct bio *rbp = bioq_first(&isc->bio_queue);
		struct bio *wbp = bioq_first(&isc->write_queue);
		bool can_write = wbp != NULL &&
		    cam_iosched_limiter_caniop(&isc->write_stats, wbp) == 0;
		bool can_read = rbp != NULL &&
		    cam_iosched_limiter_caniop(&isc->read_stats, rbp) == 0;
		if (iosched_debug > 2) {
			printf("can write %d: pending_writes %d max_writes %d\n", can_write, isc->write_stats.pending, isc->write_stats.max);
			printf("can read %d: read_stats.pending %d max_reads %d\n", can_read, isc->read_stats.pending, isc->read_stats.max);
			printf("Queued reads %d writes %d\n", isc->read_stats.queued, isc->write_stats.queued);
		}
		return can_read || can_write;
	}
#endif
	return bioq_first(&isc->bio_queue) != NULL;
}