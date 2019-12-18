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
typedef  int /*<<< orphan*/  target_id_t ;
struct cam_path {TYPE_1__* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 

target_id_t
xpt_path_target_id(struct cam_path *path)
{
	if (path->target != NULL)
		return (path->target->target_id);
	else
		return (CAM_TARGET_WILDCARD);
}