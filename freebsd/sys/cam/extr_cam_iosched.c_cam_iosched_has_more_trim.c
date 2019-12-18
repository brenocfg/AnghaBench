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
struct cam_iosched_softc {scalar_t__ trim_goal; scalar_t__ queued_trims; scalar_t__ trim_ticks; scalar_t__ last_trim_tick; int flags; int /*<<< orphan*/  trim_queue; } ;

/* Variables and functions */
 int CAM_IOSCHED_FLAG_TRIM_ACTIVE ; 
 scalar_t__ bioq_first (int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static inline bool
cam_iosched_has_more_trim(struct cam_iosched_softc *isc)
{

	/*
	 * If we've set a trim_goal, then if we exceed that allow trims
	 * to be passed back to the driver. If we've also set a tick timeout
	 * allow trims back to the driver. Otherwise, don't allow trims yet.
	 */
	if (isc->trim_goal > 0) {
		if (isc->queued_trims >= isc->trim_goal)
			return true;
		if (isc->queued_trims > 0 &&
		    isc->trim_ticks > 0 &&
		    ticks - isc->last_trim_tick > isc->trim_ticks)
			return true;
		return false;
	}

	return !(isc->flags & CAM_IOSCHED_FLAG_TRIM_ACTIVE) &&
	    bioq_first(&isc->trim_queue);
}