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
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_req_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_map_t ;
struct TYPE_4__ {int /*<<< orphan*/ * raid_map; int /*<<< orphan*/  scsi3addr; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SA_GET_RAID_MAP ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,char*,int) ; 
 int pqisrc_build_send_raid_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pqisrc_raid_map_validation (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqisrc_get_device_raidmap(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device)
{
	int ret = PQI_STATUS_SUCCESS;
	pqisrc_raid_req_t request;
	pqisrc_raid_map_t *raid_map;

	DBG_FUNC("IN\n");

	raid_map = os_mem_alloc(softs, sizeof(*raid_map));
	if (!raid_map)
		return PQI_STATUS_FAILURE;

	memset(&request, 0, sizeof(request));
	ret =  pqisrc_build_send_raid_request(softs, &request, raid_map, sizeof(*raid_map), 
			 		SA_GET_RAID_MAP, 0, device->scsi3addr, NULL);

	if (ret) {
		DBG_ERR("error in build send raid req ret=%d\n", ret);
		goto err_out;
	}

	ret = pqisrc_raid_map_validation(softs, device, raid_map);
	if (ret) {
		DBG_ERR("error in raid map validation ret=%d\n", ret);
		goto err_out;
	}

	device->raid_map = raid_map;
	DBG_FUNC("OUT\n");
	return 0;

err_out:
	os_mem_free(softs, (char*)raid_map, sizeof(*raid_map));
	DBG_FUNC("FAILED \n");
	return ret;
}