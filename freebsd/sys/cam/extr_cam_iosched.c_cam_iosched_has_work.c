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
struct cam_iosched_softc {int dummy; } ;

/* Variables and functions */
 int cam_iosched_has_flagged_work (struct cam_iosched_softc*) ; 
 int cam_iosched_has_io (struct cam_iosched_softc*) ; 
 int cam_iosched_has_more_trim (struct cam_iosched_softc*) ; 
 int iosched_debug ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static inline bool
cam_iosched_has_work(struct cam_iosched_softc *isc)
{
#ifdef CAM_IOSCHED_DYNAMIC
	if (iosched_debug > 2)
		printf("has work: %d %d %d\n", cam_iosched_has_io(isc),
		    cam_iosched_has_more_trim(isc),
		    cam_iosched_has_flagged_work(isc));
#endif

	return cam_iosched_has_io(isc) ||
		cam_iosched_has_more_trim(isc) ||
		cam_iosched_has_flagged_work(isc);
}