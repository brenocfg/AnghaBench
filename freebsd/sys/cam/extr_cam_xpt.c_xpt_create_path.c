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
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  M_CAMPATH ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (struct cam_path*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_compile_path (struct cam_path*,struct cam_periph*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cam_status
xpt_create_path(struct cam_path **new_path_ptr, struct cam_periph *perph,
		path_id_t path_id, target_id_t target_id, lun_id_t lun_id)
{
	struct	   cam_path *path;
	cam_status status;

	path = (struct cam_path *)malloc(sizeof(*path), M_CAMPATH, M_NOWAIT);

	if (path == NULL) {
		status = CAM_RESRC_UNAVAIL;
		return(status);
	}
	status = xpt_compile_path(path, perph, path_id, target_id, lun_id);
	if (status != CAM_REQ_CMP) {
		free(path, M_CAMPATH);
		path = NULL;
	}
	*new_path_ptr = path;
	return (status);
}