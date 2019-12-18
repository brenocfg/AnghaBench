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
struct cam_iosched_softc {TYPE_1__ trim_stats; int /*<<< orphan*/  last_trim_tick; int /*<<< orphan*/  queued_trims; int /*<<< orphan*/  trim_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  ticks ; 

struct bio *
cam_iosched_next_trim(struct cam_iosched_softc *isc)
{
	struct bio *bp;

	bp  = bioq_first(&isc->trim_queue);
	if (bp == NULL)
		return NULL;
	bioq_remove(&isc->trim_queue, bp);
	isc->queued_trims--;
	isc->last_trim_tick = ticks;	/* Reset the tick timer when we take trims */
#ifdef CAM_IOSCHED_DYNAMIC
	isc->trim_stats.queued--;
	isc->trim_stats.total++;
	isc->trim_stats.pending++;
#endif
	return bp;
}