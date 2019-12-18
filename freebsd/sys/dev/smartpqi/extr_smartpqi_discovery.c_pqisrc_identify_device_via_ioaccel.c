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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {TYPE_2__*** device_list; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_7__ {scalar_t__ devtype; scalar_t__ ioaccel_handle; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ DISK_DEVICE ; 
 int PQI_MAX_DEVICES ; 
 int PQI_MAX_MULTILUN ; 
 scalar_t__ pqisrc_is_logical_device (TYPE_2__*) ; 

__attribute__((used)) static pqi_scsi_dev_t *pqisrc_identify_device_via_ioaccel(
	pqisrc_softstate_t *softs, uint32_t ioaccel_handle)
{
	pqi_scsi_dev_t *device;
	int i,j;
	DBG_FUNC("IN\n");	
	for(i = 0; i < PQI_MAX_DEVICES; i++) {
		for(j = 0; j < PQI_MAX_MULTILUN; j++) {
			if(softs->device_list[i][j] == NULL)
				continue;
			device = softs->device_list[i][j];
			if (device->devtype != DISK_DEVICE)
				continue;
			if (pqisrc_is_logical_device(device))
				continue;
			if (device->ioaccel_handle == ioaccel_handle)
				return device;
		}
	}
	DBG_FUNC("OUT\n");

	return NULL;
}