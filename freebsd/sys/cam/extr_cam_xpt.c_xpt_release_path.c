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
struct cam_path {int /*<<< orphan*/ * bus; int /*<<< orphan*/ * target; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  xpt_release_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_target (int /*<<< orphan*/ *) ; 

void
xpt_release_path(struct cam_path *path)
{
	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("xpt_release_path\n"));
	if (path->device != NULL) {
		xpt_release_device(path->device);
		path->device = NULL;
	}
	if (path->target != NULL) {
		xpt_release_target(path->target);
		path->target = NULL;
	}
	if (path->bus != NULL) {
		xpt_release_bus(path->bus);
		path->bus = NULL;
	}
}