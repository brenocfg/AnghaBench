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
typedef  union ccb {int dummy; } ccb ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_3__ {scalar_t__ priority; } ;
struct ccb_hdr {TYPE_1__ pinfo; } ;
struct cam_periph {scalar_t__ immediate_priority; int /*<<< orphan*/  ccb_list; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PRIBIO ; 
 struct ccb_hdr* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_sleep (struct cam_periph*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ periph_links ; 
 int /*<<< orphan*/  xpt_run_allocq (struct cam_periph*,int /*<<< orphan*/ ) ; 

union ccb *
cam_periph_getccb(struct cam_periph *periph, u_int32_t priority)
{
	struct ccb_hdr *ccb_h;

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("cam_periph_getccb\n"));
	cam_periph_assert(periph, MA_OWNED);
	while ((ccb_h = SLIST_FIRST(&periph->ccb_list)) == NULL ||
	    ccb_h->pinfo.priority != priority) {
		if (priority < periph->immediate_priority) {
			periph->immediate_priority = priority;
			xpt_run_allocq(periph, 0);
		} else
			cam_periph_sleep(periph, &periph->ccb_list, PRIBIO,
			    "cgticb", 0);
	}
	SLIST_REMOVE_HEAD(&periph->ccb_list, periph_links.sle);
	return ((union ccb *)ccb_h);
}