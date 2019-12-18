#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_4__ {int offload_enabled; int /*<<< orphan*/ * raid_map; scalar_t__ offload_to_mirror; int /*<<< orphan*/  offload_enabled_pending; int /*<<< orphan*/  offload_config; int /*<<< orphan*/  phys_connector; int /*<<< orphan*/  box; int /*<<< orphan*/  bay; int /*<<< orphan*/  path_map; int /*<<< orphan*/  active_path_index; int /*<<< orphan*/  volume_status; int /*<<< orphan*/  ioaccel_handle; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  raid_level; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  is_external_raid_device; int /*<<< orphan*/  is_physical_device; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; int /*<<< orphan*/  expose_device; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void pqisrc_exist_device_update(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device_exist,
	pqi_scsi_dev_t *new_device)
{
	DBG_FUNC("IN\n");
	device_exist->expose_device = new_device->expose_device;
	memcpy(device_exist->vendor, new_device->vendor,
		sizeof(device_exist->vendor));
	memcpy(device_exist->model, new_device->model,
		sizeof(device_exist->model));
	device_exist->is_physical_device = new_device->is_physical_device;
	device_exist->is_external_raid_device =
		new_device->is_external_raid_device;
	device_exist->sas_address = new_device->sas_address;
	device_exist->raid_level = new_device->raid_level;
	device_exist->queue_depth = new_device->queue_depth;
	device_exist->ioaccel_handle = new_device->ioaccel_handle;
	device_exist->volume_status = new_device->volume_status;
	device_exist->active_path_index = new_device->active_path_index;
	device_exist->path_map = new_device->path_map;
	device_exist->bay = new_device->bay;
	memcpy(device_exist->box, new_device->box,
		sizeof(device_exist->box));
	memcpy(device_exist->phys_connector, new_device->phys_connector,
		sizeof(device_exist->phys_connector));
	device_exist->offload_config = new_device->offload_config;
	device_exist->offload_enabled = false;
	device_exist->offload_enabled_pending =
		new_device->offload_enabled_pending;
	device_exist->offload_to_mirror = 0;
	if (device_exist->raid_map)
		os_mem_free(softs,
			    (char *)device_exist->raid_map,
			    sizeof(*device_exist->raid_map));
	device_exist->raid_map = new_device->raid_map;
	/* To prevent this from being freed later. */
	new_device->raid_map = NULL;
	DBG_FUNC("OUT\n");
}