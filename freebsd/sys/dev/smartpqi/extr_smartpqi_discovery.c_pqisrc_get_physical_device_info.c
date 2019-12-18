#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_8__ {int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  device_type; int /*<<< orphan*/  bay; int /*<<< orphan*/  phys_connector; int /*<<< orphan*/  box; int /*<<< orphan*/  path_map; int /*<<< orphan*/  active_path_index; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;
struct TYPE_9__ {int /*<<< orphan*/  phys_bay_in_box; int /*<<< orphan*/  alternate_paths_phys_connector; int /*<<< orphan*/  alternate_paths_phys_box_on_port; int /*<<< orphan*/  redundant_path_present_map; int /*<<< orphan*/  active_path_number; int /*<<< orphan*/  device_type; int /*<<< orphan*/  current_queue_depth_limit; } ;
typedef  TYPE_2__ bmic_ident_physdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DISC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  LE_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQI_PHYSICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int pqisrc_identify_physical_disk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static void pqisrc_get_physical_device_info(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device,
	bmic_ident_physdev_t *id_phys)
{
	int ret = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");
	memset(id_phys, 0, sizeof(*id_phys));

	ret= pqisrc_identify_physical_disk(softs, device,
		id_phys, sizeof(*id_phys));
	if (ret) {
		device->queue_depth = PQI_PHYSICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH;
		return;
	}

	device->queue_depth =
		LE_16(id_phys->current_queue_depth_limit);
	device->device_type = id_phys->device_type;
	device->active_path_index = id_phys->active_path_number;
	device->path_map = id_phys->redundant_path_present_map;
	memcpy(&device->box,
		&id_phys->alternate_paths_phys_box_on_port,
		sizeof(device->box));
	memcpy(&device->phys_connector,
		&id_phys->alternate_paths_phys_connector,
		sizeof(device->phys_connector));
	device->bay = id_phys->phys_bay_in_box;

	DBG_DISC("BMIC DEV_TYPE: %x QUEUE DEPTH: 0x%x \n",  device->device_type, device->queue_depth);
	DBG_FUNC("OUT\n");
}