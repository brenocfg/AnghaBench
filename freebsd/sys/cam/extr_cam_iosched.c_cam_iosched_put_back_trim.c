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
struct TYPE_2__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  total; int /*<<< orphan*/  queued; } ;
struct cam_iosched_softc {scalar_t__ queued_trims; TYPE_1__ trim_stats; int /*<<< orphan*/  last_trim_tick; int /*<<< orphan*/  trim_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_insert_head (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  ticks ; 

void
cam_iosched_put_back_trim(struct cam_iosched_softc *isc, struct bio *bp)
{
	bioq_insert_head(&isc->trim_queue, bp);
	if (isc->queued_trims == 0)
		isc->last_trim_tick = ticks;
	isc->queued_trims++;
#ifdef CAM_IOSCHED_DYNAMIC
	isc->trim_stats.queued++;
	isc->trim_stats.total--;		/* since we put it back, don't double count */
	isc->trim_stats.pending--;
#endif
}