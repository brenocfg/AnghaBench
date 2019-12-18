#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct ccb_setasync {int /*<<< orphan*/  callback_arg; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_path*,struct ccb_getdev*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  func_code; } ;
struct ccb_getdev {TYPE_3__ ccb_h; } ;
struct cam_path {int dummy; } ;
struct cam_ed {int flags; int /*<<< orphan*/  lun_id; TYPE_2__* target; } ;
struct TYPE_5__ {int /*<<< orphan*/  target_id; TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_FOUND_DEVICE ; 
 int CAM_DEV_UNCONFIGURED ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  XPT_GDEV_TYPE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_path*,struct ccb_getdev*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_compile_path (struct cam_path*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_3__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xptsetasyncfunc(struct cam_ed *device, void *arg)
{
	struct cam_path path;
	struct ccb_getdev cgd;
	struct ccb_setasync *csa = (struct ccb_setasync *)arg;

	/*
	 * Don't report unconfigured devices (Wildcard devs,
	 * devices only for target mode, device instances
	 * that have been invalidated but are waiting for
	 * their last reference count to be released).
	 */
	if ((device->flags & CAM_DEV_UNCONFIGURED) != 0)
		return (1);

	xpt_compile_path(&path,
			 NULL,
			 device->target->bus->path_id,
			 device->target->target_id,
			 device->lun_id);
	xpt_setup_ccb(&cgd.ccb_h, &path, CAM_PRIORITY_NORMAL);
	cgd.ccb_h.func_code = XPT_GDEV_TYPE;
	xpt_action((union ccb *)&cgd);
	csa->callback(csa->callback_arg,
			    AC_FOUND_DEVICE,
			    &path, &cgd);
	xpt_release_path(&path);

	return(1);
}