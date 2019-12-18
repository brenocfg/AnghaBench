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
struct TYPE_8__ {TYPE_2__*** device_list; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_9__ {scalar_t__ volume_offline; int /*<<< orphan*/  scsi3addr; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;
typedef  int /*<<< orphan*/  device_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DEVICE_CHANGED ; 
 int /*<<< orphan*/  DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  DEVICE_UNCHANGED ; 
 int PQI_MAX_DEVICES ; 
 int PQI_MAX_MULTILUN ; 
 scalar_t__ pqisrc_device_equal (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ pqisrc_scsi3addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_status_t pqisrc_scsi_find_entry(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device_to_find,
	pqi_scsi_dev_t **same_device)
{
	pqi_scsi_dev_t *device;
	int i,j;
	DBG_FUNC("IN\n");
	for(i = 0; i < PQI_MAX_DEVICES; i++) {
		for(j = 0; j < PQI_MAX_MULTILUN; j++) {
			if(softs->device_list[i][j] == NULL)
				continue;
			device = softs->device_list[i][j];
			if (pqisrc_scsi3addr_equal(device_to_find->scsi3addr,
				device->scsi3addr)) {
				*same_device = device;
				if (pqisrc_device_equal(device_to_find, device)) {
					if (device_to_find->volume_offline)
						return DEVICE_CHANGED;
					return DEVICE_UNCHANGED;
				}
				return DEVICE_CHANGED;
			}
		}
	}
	DBG_FUNC("OUT\n");

	return DEVICE_NOT_FOUND;
}