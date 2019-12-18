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
typedef  int /*<<< orphan*/  target_id_t ;
struct cam_periph {int dummy; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  int /*<<< orphan*/  cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_create_path (struct cam_path**,struct cam_periph*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cam_status
xpt_create_path_unlocked(struct cam_path **new_path_ptr,
			 struct cam_periph *periph, path_id_t path_id,
			 target_id_t target_id, lun_id_t lun_id)
{

	return (xpt_create_path(new_path_ptr, periph, path_id, target_id,
	    lun_id));
}