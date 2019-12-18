#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  prop_buf ;
struct TYPE_6__ {TYPE_2__* ocs; } ;
typedef  TYPE_1__ ocs_xport_t ;
struct TYPE_7__ {int auto_xfer_rdy_size; int /*<<< orphan*/  desc; int /*<<< orphan*/  hw; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_BLK_SIZE ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_CAPABLE ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_P_TYPE ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_SIZE ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_T10_ENABLE ; 
 int TRUE ; 
 scalar_t__ ocs_get_property (char*,char*,int) ; 
 int /*<<< orphan*/  ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ocs_hw_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_2__*,char*,...) ; 
 scalar_t__ ocs_strlen (char*) ; 
 int ocs_strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_xport_initialize_auto_xfer_ready(ocs_xport_t *xport)
{
	ocs_t *ocs = xport->ocs;
	uint32_t auto_xfer_rdy;
	char prop_buf[32];
	uint32_t ramdisc_blocksize = 512;
	uint8_t p_type = 0;

	ocs_hw_get(&ocs->hw, OCS_HW_AUTO_XFER_RDY_CAPABLE, &auto_xfer_rdy);
	if (!auto_xfer_rdy) {
		ocs->auto_xfer_rdy_size = 0;
		ocs_log_test(ocs, "Cannot enable auto xfer rdy for this port\n");
		return 0;
	}

	if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_SIZE, ocs->auto_xfer_rdy_size)) {
		ocs_log_test(ocs, "%s: Can't set auto xfer rdy mode\n", ocs->desc);
		return -1;
	}

	/*
	 * Determine if we are doing protection in the backend. We are looking
	 * at the modules parameters here. The backend cannot allow a format
	 * command to change the protection mode when using this feature,
	 * otherwise the firmware will not do the proper thing.
	 */
	if (ocs_get_property("p_type", prop_buf, sizeof(prop_buf)) == 0) {
		p_type = ocs_strtoul(prop_buf, 0, 0);
	}
	if (ocs_get_property("ramdisc_blocksize", prop_buf, sizeof(prop_buf)) == 0) {
		ramdisc_blocksize = ocs_strtoul(prop_buf, 0, 0);
	}
	if (ocs_get_property("external_dif", prop_buf, sizeof(prop_buf)) == 0) {
		if(ocs_strlen(prop_buf)) {
			if (p_type == 0) {
				p_type = 1;
			}
		}
	}

	if (p_type != 0) {
		if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_T10_ENABLE, TRUE)) {
			ocs_log_test(ocs, "%s: Can't set auto xfer rdy mode\n", ocs->desc);
			return -1;
		}
		if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_BLK_SIZE, ramdisc_blocksize)) {
			ocs_log_test(ocs, "%s: Can't set auto xfer rdy blk size\n", ocs->desc);
			return -1;
		}
		if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_P_TYPE, p_type)) {
			ocs_log_test(ocs, "%s: Can't set auto xfer rdy mode\n", ocs->desc);
			return -1;
		}
		if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA, TRUE)) {
			ocs_log_test(ocs, "%s: Can't set auto xfer rdy ref tag\n", ocs->desc);
			return -1;
		}
		if (ocs_hw_set(&ocs->hw, OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID, FALSE)) {
			ocs_log_test(ocs, "%s: Can't set auto xfer rdy app tag valid\n", ocs->desc);
			return -1;
		}
	}
	ocs_log_debug(ocs, "Auto xfer rdy is enabled, p_type=%d, blksize=%d\n",
		p_type, ramdisc_blocksize);
	return 0;
}