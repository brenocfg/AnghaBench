#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ioaccel_handle; } ;
typedef  TYPE_1__ raidmap_data_t ;
struct TYPE_12__ {TYPE_4__*** device_list; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_13__ {int /*<<< orphan*/  row_cnt; int /*<<< orphan*/  metadata_disks_per_row; int /*<<< orphan*/  data_disks_per_row; int /*<<< orphan*/  layout_map_count; TYPE_1__* dev_data; } ;
typedef  TYPE_3__ pqisrc_raid_map_t ;
struct TYPE_14__ {scalar_t__ devtype; unsigned int queue_depth; int offload_enabled; int offload_enabled_pending; TYPE_3__* raid_map; int /*<<< orphan*/ * scsi3addr; } ;
typedef  TYPE_4__ pqi_scsi_dev_t ;

/* Variables and functions */
 scalar_t__ BE_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_WARN (char*,unsigned long long) ; 
 scalar_t__ DISK_DEVICE ; 
 unsigned int LE_16 (int /*<<< orphan*/ ) ; 
 unsigned int PQI_LOGICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH ; 
 unsigned int PQI_MAX_DEVICES ; 
 unsigned int PQI_MAX_MULTILUN ; 
 int /*<<< orphan*/  os_mem_free (TYPE_2__*,char*,int) ; 
 TYPE_4__* pqisrc_identify_device_via_ioaccel (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pqisrc_is_external_raid_device (TYPE_4__*) ; 
 int /*<<< orphan*/  pqisrc_is_logical_device (TYPE_4__*) ; 

__attribute__((used)) static void pqisrc_update_log_dev_qdepth(pqisrc_softstate_t *softs)
{
	unsigned i;
	unsigned phys_dev_num;
	unsigned num_raidmap_entries;
	unsigned queue_depth;
	pqisrc_raid_map_t *raid_map;
	pqi_scsi_dev_t *device;
	raidmap_data_t *dev_data;
	pqi_scsi_dev_t *phys_disk;
	unsigned j;
	unsigned k;

	DBG_FUNC("IN\n");

	for(i = 0; i < PQI_MAX_DEVICES; i++) {
		for(j = 0; j < PQI_MAX_MULTILUN; j++) {
			if(softs->device_list[i][j] == NULL)
				continue;
			device = softs->device_list[i][j];
			if (device->devtype != DISK_DEVICE)
				continue;
			if (!pqisrc_is_logical_device(device))
				continue;
			if (pqisrc_is_external_raid_device(device))
				continue;
			device->queue_depth = PQI_LOGICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH;
			raid_map = device->raid_map;
			if (!raid_map)
				return;
			dev_data = raid_map->dev_data;
			phys_dev_num = LE_16(raid_map->layout_map_count) *
					(LE_16(raid_map->data_disks_per_row) +
					LE_16(raid_map->metadata_disks_per_row));
			num_raidmap_entries = phys_dev_num *
						LE_16(raid_map->row_cnt);

			queue_depth = 0;
			for (k = 0; k < num_raidmap_entries; k++) {
				phys_disk = pqisrc_identify_device_via_ioaccel(softs,
						dev_data[k].ioaccel_handle);

				if (!phys_disk) {
					DBG_WARN(
					"Failed to find physical disk handle for logical drive %016llx\n",
						(unsigned long long)BE_64(device->scsi3addr[0]));
					device->offload_enabled = false;
					device->offload_enabled_pending = false;
					if (raid_map)
						os_mem_free(softs, (char *)raid_map, sizeof(*raid_map));
					device->raid_map = NULL;
					return;
				}

				queue_depth += phys_disk->queue_depth;
			}

			device->queue_depth = queue_depth;
		} /* end inner loop */
	}/* end outer loop */
	DBG_FUNC("OUT\n");
}