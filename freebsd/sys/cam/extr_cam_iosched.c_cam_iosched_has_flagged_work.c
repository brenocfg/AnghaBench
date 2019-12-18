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
struct cam_iosched_softc {int flags; } ;

/* Variables and functions */
 int CAM_IOSCHED_FLAG_WORK_FLAGS ; 

__attribute__((used)) static inline bool
cam_iosched_has_flagged_work(struct cam_iosched_softc *isc)
{
	return !!(isc->flags & CAM_IOSCHED_FLAG_WORK_FLAGS);
}