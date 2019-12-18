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
typedef  void* uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_6__ {void** cdb; } ;
typedef  TYPE_1__ pqisrc_raid_req_t ;
struct TYPE_7__ {int /*<<< orphan*/  scsi3addr; } ;
typedef  TYPE_2__ pqi_scsi_dev_t ;
typedef  int /*<<< orphan*/  bmic_ident_physdev_t ;

/* Variables and functions */
 int BMIC_GET_DRIVE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMIC_IDENTIFY_PHYSICAL_DEVICE ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_SUCCESS ; 
 scalar_t__ RAID_CTLR_LUNID ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pqisrc_build_send_raid_request (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqisrc_identify_physical_disk(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device,
	bmic_ident_physdev_t *buff,
	int buf_len)
{
	int ret = PQI_STATUS_SUCCESS;
	uint16_t bmic_device_index;
	pqisrc_raid_req_t request;


	DBG_FUNC("IN\n");

	memset(&request, 0, sizeof(request));	
	bmic_device_index = BMIC_GET_DRIVE_NUMBER(device->scsi3addr);
	request.cdb[2] = (uint8_t)bmic_device_index;
	request.cdb[9] = (uint8_t)(bmic_device_index >> 8);

	ret =  pqisrc_build_send_raid_request(softs, &request, buff, buf_len, 
				BMIC_IDENTIFY_PHYSICAL_DEVICE, 0, (uint8_t *)RAID_CTLR_LUNID, NULL);
	DBG_FUNC("OUT\n");
	return ret;
}