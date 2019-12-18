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
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_3__ {int /*<<< orphan*/  raid_level; int /*<<< orphan*/  queue_depth; scalar_t__ expose_device; scalar_t__ offload_enabled_pending; scalar_t__ offload_config; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INFO (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_raidlevel_to_string (int /*<<< orphan*/ ) ; 

void pqisrc_display_device_info(pqisrc_softstate_t *softs,
	char *action, pqi_scsi_dev_t *device)
{
	DBG_INFO( "%s scsi BTL %d:%d:%d:  %.8s %.16s %-12s SSDSmartPathCap%c En%c Exp%c qd=%d\n",
		action,
		device->bus,
		device->target,
		device->lun,
		device->vendor,
		device->model,
		pqisrc_raidlevel_to_string(device->raid_level),
		device->offload_config ? '+' : '-',
		device->offload_enabled_pending ? '+' : '-',
		device->expose_device ? '+' : '-',
		device->queue_depth);
	pqisrc_raidlevel_to_string(device->raid_level); /* To use this function */
}