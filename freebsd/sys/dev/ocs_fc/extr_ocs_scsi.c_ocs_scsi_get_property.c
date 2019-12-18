#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  io_pool; } ;
typedef  TYPE_1__ ocs_xport_t ;
struct TYPE_6__ {int ctrlmask; int /*<<< orphan*/  hw; TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int ocs_scsi_property_e ;

/* Variables and functions */
 int OCS_CTRLMASK_TEST_CHAINED_SGLS ; 
 int OCS_FC_MAX_SGL ; 
 int /*<<< orphan*/  OCS_HW_DIF_CAPABLE ; 
 int /*<<< orphan*/  OCS_HW_DIF_MULTI_SEPARATE ; 
 int /*<<< orphan*/  OCS_HW_MAX_SGE ; 
 int /*<<< orphan*/  OCS_HW_N_SGL ; 
 int /*<<< orphan*/  OCS_HW_SEND_FRAME_CAPABLE ; 
#define  OCS_SCSI_DIF_CAPABLE 134 
#define  OCS_SCSI_DIF_MULTI_SEPARATE 133 
#define  OCS_SCSI_ENABLE_TASK_SET_FULL 132 
#define  OCS_SCSI_MAX_FIRST_BURST 131 
#define  OCS_SCSI_MAX_IOS 130 
#define  OCS_SCSI_MAX_SGE 129 
#define  OCS_SCSI_MAX_SGL 128 
 int /*<<< orphan*/  ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int ocs_io_pool_allocated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_2__*,char*,int) ; 

uint32_t
ocs_scsi_get_property(ocs_t *ocs, ocs_scsi_property_e prop)
{
	ocs_xport_t *xport = ocs->xport;
	uint32_t	val;

	switch (prop) {
	case OCS_SCSI_MAX_SGE:
		if (0 == ocs_hw_get(&ocs->hw, OCS_HW_MAX_SGE, &val)) {
			return val;
		}
		break;
	case OCS_SCSI_MAX_SGL:
		if (ocs->ctrlmask & OCS_CTRLMASK_TEST_CHAINED_SGLS) {
			/*
			 * If chain SGL test-mode is enabled, the number of HW SGEs
			 * has been limited; report back original max.
			 */
			return (OCS_FC_MAX_SGL);
		}
		if (0 == ocs_hw_get(&ocs->hw, OCS_HW_N_SGL, &val)) {
			return val;
		}
		break;
	case OCS_SCSI_MAX_IOS:
		return ocs_io_pool_allocated(xport->io_pool);
	case OCS_SCSI_DIF_CAPABLE:
	        if (0 == ocs_hw_get(&ocs->hw, OCS_HW_DIF_CAPABLE, &val)) {
	                return val;
	        }
		break;
	case OCS_SCSI_MAX_FIRST_BURST:
		return 0;
	case OCS_SCSI_DIF_MULTI_SEPARATE:
	        if (ocs_hw_get(&ocs->hw, OCS_HW_DIF_MULTI_SEPARATE, &val) == 0) {
	                return val;
	        }
		break;
	case OCS_SCSI_ENABLE_TASK_SET_FULL:
		/* Return FALSE if we are send frame capable */
		if (ocs_hw_get(&ocs->hw, OCS_HW_SEND_FRAME_CAPABLE, &val) == 0) {
			return ! val;
		}
		break;
	default:
		break;
	}

	ocs_log_debug(ocs, "invalid property request %d\n", prop);
	return 0;
}