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
struct cam_path {int /*<<< orphan*/ * device; int /*<<< orphan*/ * target; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_acquire_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_acquire_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_acquire_target (int /*<<< orphan*/ *) ; 

void
xpt_copy_path(struct cam_path *new_path, struct cam_path *path)
{

	*new_path = *path;
	if (path->bus != NULL)
		xpt_acquire_bus(path->bus);
	if (path->target != NULL)
		xpt_acquire_target(path->target);
	if (path->device != NULL)
		xpt_acquire_device(path->device);
}