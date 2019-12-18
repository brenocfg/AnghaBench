#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int target_lun_valid; int /*<<< orphan*/ * scsi3addr; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DISC (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int GET_LE32 (int /*<<< orphan*/ *) ; 
 int PQI_CTLR_INDEX ; 
 int PQI_EXTERNAL_RAID_VOLUME_BUS ; 
 int PQI_HBA_BUS ; 
 int PQI_RAID_VOLUME_BUS ; 
 scalar_t__ pqisrc_is_external_raid_device (TYPE_1__*) ; 
 scalar_t__ pqisrc_is_hba_lunid (int /*<<< orphan*/ *) ; 
 scalar_t__ pqisrc_is_logical_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_set_btl (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void pqisrc_assign_btl(pqi_scsi_dev_t *device)
{
	uint8_t *scsi3addr;
	uint32_t lunid;
	uint32_t bus;
	uint32_t target;
	uint32_t lun;
	DBG_FUNC("IN\n");

	scsi3addr = device->scsi3addr;
	lunid = GET_LE32(scsi3addr);

	if (pqisrc_is_hba_lunid(scsi3addr)) {
		/* The specified device is the controller. */
		pqisrc_set_btl(device, PQI_HBA_BUS, PQI_CTLR_INDEX, lunid & 0x3fff);
		device->target_lun_valid = true;
		return;
	}

	if (pqisrc_is_logical_device(device)) {
		if (pqisrc_is_external_raid_device(device)) {
			DBG_DISC("External Raid Device!!!");
			bus = PQI_EXTERNAL_RAID_VOLUME_BUS;
			target = (lunid >> 16) & 0x3fff;
			lun = lunid & 0xff;
		} else {
			bus = PQI_RAID_VOLUME_BUS;
			lun = 0;
			target = lunid & 0x3fff;
		}
		pqisrc_set_btl(device, bus, target, lun);
		device->target_lun_valid = true;
		return;
	}

	DBG_FUNC("OUT\n");
}