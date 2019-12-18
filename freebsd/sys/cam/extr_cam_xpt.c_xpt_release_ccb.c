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
struct TYPE_3__ {TYPE_2__* path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct cam_periph {int /*<<< orphan*/  periph_allocated; } ;
struct cam_ed {int /*<<< orphan*/  ccbq; } ;
struct TYPE_4__ {struct cam_periph* periph; struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_XPT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_ccbq_release_opening (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_run_allocq (struct cam_periph*,int /*<<< orphan*/ ) ; 

void
xpt_release_ccb(union ccb *free_ccb)
{
	struct	 cam_ed *device;
	struct	 cam_periph *periph;

	CAM_DEBUG_PRINT(CAM_DEBUG_XPT, ("xpt_release_ccb\n"));
	xpt_path_assert(free_ccb->ccb_h.path, MA_OWNED);
	device = free_ccb->ccb_h.path->device;
	periph = free_ccb->ccb_h.path->periph;

	xpt_free_ccb(free_ccb);
	periph->periph_allocated--;
	cam_ccbq_release_opening(&device->ccbq);
	xpt_run_allocq(periph, 0);
}