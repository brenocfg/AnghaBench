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
typedef  size_t uint32_t ;
typedef  int u_int32_t ;
struct pqisrc_softstate {TYPE_2__*** device_list; } ;
struct TYPE_3__ {size_t target_id; size_t target_lun; } ;
struct ccb_getdev {TYPE_1__ ccb_h; } ;
struct cam_path {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_depth; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;

/* Variables and functions */
#define  AC_FOUND_DEVICE 128 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PQI_CTLR_INDEX ; 
 int /*<<< orphan*/  smartpqi_adjust_queue_depth (struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smartpqi_async(void *callback_arg, u_int32_t code,
		struct cam_path *path, void *arg)
{
	struct pqisrc_softstate *softs;
	softs = (struct pqisrc_softstate*)callback_arg;

	DBG_FUNC("IN\n");

	switch (code) {
		case AC_FOUND_DEVICE:
		{
			struct ccb_getdev *cgd;
			cgd = (struct ccb_getdev *)arg;
			if (cgd == NULL) {
				break;
			}
			uint32_t t_id = cgd->ccb_h.target_id;

			if (t_id <= (PQI_CTLR_INDEX - 1)) {
				if (softs != NULL) {
					pqi_scsi_dev_t *dvp = softs->device_list[t_id][cgd->ccb_h.target_lun];
					smartpqi_adjust_queue_depth(path,
							dvp->queue_depth);
				}
			}
			break;
		}
		default:
			break;
	}

	DBG_FUNC("OUT\n");
}