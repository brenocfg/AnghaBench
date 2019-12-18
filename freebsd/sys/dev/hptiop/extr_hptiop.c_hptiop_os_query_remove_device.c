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
struct hpt_iop_hba {int /*<<< orphan*/  pciunit; int /*<<< orphan*/  pcidev; TYPE_1__* sim; } ;
struct cam_periph {int refcount; } ;
struct cam_path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
 int CAM_REQ_CMP ; 
 struct cam_periph* cam_periph_find (struct cam_path*,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

__attribute__((used)) static  int hptiop_os_query_remove_device(struct hpt_iop_hba * hba,
						int target_id)
{
	struct cam_periph       *periph = NULL;
	struct cam_path         *path;
	int                     status, retval = 0;

	status = xpt_create_path(&path, NULL, hba->sim->path_id, target_id, 0);

	if (status == CAM_REQ_CMP) {
		if ((periph = cam_periph_find(path, "da")) != NULL) {
			if (periph->refcount >= 1) {
				device_printf(hba->pcidev, "%d ,"
					"target_id=0x%x,"
					"refcount=%d",
				    hba->pciunit, target_id, periph->refcount);
				retval = -1;
			}
		}
		xpt_free_path(path);
	}
	return retval;
}