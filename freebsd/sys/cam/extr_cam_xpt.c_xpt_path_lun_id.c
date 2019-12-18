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
struct cam_path {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  lun_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  lun_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 

lun_id_t
xpt_path_lun_id(struct cam_path *path)
{
	if (path->device != NULL)
		return (path->device->lun_id);
	else
		return (CAM_LUN_WILDCARD);
}