#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ enable_task_set_full; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_SCSI_ENABLE_TASK_SET_FULL ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,char*) ; 
 scalar_t__ ocs_scsi_get_property (TYPE_1__*,int /*<<< orphan*/ ) ; 

int32_t
ocs_scsi_tgt_new_device(ocs_t *ocs)
{
	ocs->enable_task_set_full = ocs_scsi_get_property(ocs, 
					OCS_SCSI_ENABLE_TASK_SET_FULL);
	ocs_log_debug(ocs, "task set full processing is %s\n",
		ocs->enable_task_set_full ? "enabled" : "disabled");

	return 0;
}