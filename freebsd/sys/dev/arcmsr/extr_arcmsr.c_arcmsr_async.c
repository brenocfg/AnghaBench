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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct AdapterControlBlock {int dummy; } ;

/* Variables and functions */
#define  AC_LOST_DEVICE 128 
 int /*<<< orphan*/  ARCMSR_MAX_TARGETID ; 
 int /*<<< orphan*/  ARCMSR_MAX_TARGETLUN ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_target_id (struct cam_path*) ; 

__attribute__((used)) static void arcmsr_async(void *cb_arg, u_int32_t code, struct cam_path *path, void *arg)
{
	struct AdapterControlBlock *acb;
	u_int8_t target_id, target_lun;
	struct cam_sim *sim;

	sim = (struct cam_sim *) cb_arg;
	acb =(struct AdapterControlBlock *) cam_sim_softc(sim);
	switch (code) {
	case AC_LOST_DEVICE:
		target_id = xpt_path_target_id(path);
		target_lun = xpt_path_lun_id(path);
		if((target_id > ARCMSR_MAX_TARGETID) || (target_lun > ARCMSR_MAX_TARGETLUN)) {
			break;
		}
	//	printf("%s:scsi id=%d lun=%d device lost \n", device_get_name(acb->pci_dev), target_id, target_lun);
		break;
	default:
		break;
	}
}