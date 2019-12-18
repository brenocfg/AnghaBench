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
struct cam_periph {int dummy; } ;
struct cam_iosched_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 scalar_t__ cam_iosched_has_work (struct cam_iosched_softc*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

void
cam_iosched_schedule(struct cam_iosched_softc *isc, struct cam_periph *periph)
{

	if (cam_iosched_has_work(isc))
		xpt_schedule(periph, CAM_PRIORITY_NORMAL);
}