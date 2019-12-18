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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  func_code; } ;
struct ccb_getdevstats {int /*<<< orphan*/  last_reset; TYPE_1__ ccb_h; } ;
struct cam_periph {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  XPT_GDEV_STATS ; 
 int /*<<< orphan*/  cam_periph_freeze_after_event (struct cam_periph*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cam_periph_bus_settle(struct cam_periph *periph, u_int bus_settle)
{
	struct ccb_getdevstats cgds;

	xpt_setup_ccb(&cgds.ccb_h, periph->path, CAM_PRIORITY_NORMAL);
	cgds.ccb_h.func_code = XPT_GDEV_STATS;
	xpt_action((union ccb *)&cgds);
	cam_periph_freeze_after_event(periph, &cgds.last_reset, bus_settle);
}