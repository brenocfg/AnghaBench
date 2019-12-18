#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int task_attribute; scalar_t__ rddata; scalar_t__ wrdata; } ;
typedef  TYPE_1__ fcp_cmnd_iu_t ;

/* Variables and functions */
#define  FCP_TASK_ATTR_ACA 132 
#define  FCP_TASK_ATTR_HEAD_OF_QUEUE 131 
#define  FCP_TASK_ATTR_ORDERED 130 
#define  FCP_TASK_ATTR_SIMPLE 129 
#define  FCP_TASK_ATTR_UNTAGGED 128 
 int /*<<< orphan*/  OCS_SCSI_CMD_ACA ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_DIR_IN ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_DIR_OUT ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_HEAD_OF_QUEUE ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_ORDERED ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_SIMPLE ; 
 int /*<<< orphan*/  OCS_SCSI_CMD_UNTAGGED ; 

__attribute__((used)) static uint32_t
ocs_get_flags_fcp_cmd(fcp_cmnd_iu_t *cmnd)
{
	uint32_t flags = 0;
	switch (cmnd->task_attribute) {
	case FCP_TASK_ATTR_SIMPLE:
		flags |= OCS_SCSI_CMD_SIMPLE;
		break;
	case FCP_TASK_ATTR_HEAD_OF_QUEUE:
		flags |= OCS_SCSI_CMD_HEAD_OF_QUEUE;
		break;
	case FCP_TASK_ATTR_ORDERED:
		flags |= OCS_SCSI_CMD_ORDERED;
		break;
	case FCP_TASK_ATTR_ACA:
		flags |= OCS_SCSI_CMD_ACA;
		break;
	case FCP_TASK_ATTR_UNTAGGED:
		flags |= OCS_SCSI_CMD_UNTAGGED;
		break;
	}
	if (cmnd->wrdata)
		flags |= OCS_SCSI_CMD_DIR_IN;
	if (cmnd->rddata)
		flags |= OCS_SCSI_CMD_DIR_OUT;

	return flags;
}