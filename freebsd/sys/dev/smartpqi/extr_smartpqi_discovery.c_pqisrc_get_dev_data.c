#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_7__ {int devtype; scalar_t__ volume_status; int volume_offline; int is_obdr_device; int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  raid_level; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DISC (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int DISK_DEVICE ; 
 int /*<<< orphan*/  OBDR_SIG_LEN ; 
 size_t OBDR_SIG_OFFSET ; 
 int /*<<< orphan*/  OBDR_TAPE_INQ_SIZE ; 
 int /*<<< orphan*/  OBDR_TAPE_SIG ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int ROM_DEVICE ; 
 scalar_t__ SA_LV_OK ; 
 int /*<<< orphan*/  SA_RAID_UNKNOWN ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int* os_mem_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_get_dev_ioaccel_status (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_get_dev_raid_level (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ pqisrc_get_dev_vol_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pqisrc_is_external_raid_device (TYPE_1__*) ; 
 scalar_t__ pqisrc_is_logical_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_sanitize_inquiry_string (int*,int) ; 
 int pqisrc_send_scsi_inquiry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqisrc_get_dev_data(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device)
{
	int ret = PQI_STATUS_SUCCESS;
	uint8_t *inq_buff;

	DBG_FUNC("IN\n");

	inq_buff = os_mem_alloc(softs, OBDR_TAPE_INQ_SIZE);
	if (!inq_buff)
		return PQI_STATUS_FAILURE;

	/* Send an inquiry to the device to see what it is. */
	ret = pqisrc_send_scsi_inquiry(softs, device->scsi3addr, 0, inq_buff,
		OBDR_TAPE_INQ_SIZE);
	if (ret)
		goto err_out;
	pqisrc_sanitize_inquiry_string(&inq_buff[8], 8);
	pqisrc_sanitize_inquiry_string(&inq_buff[16], 16);

	device->devtype = inq_buff[0] & 0x1f;
	memcpy(device->vendor, &inq_buff[8],
		sizeof(device->vendor));
	memcpy(device->model, &inq_buff[16],
		sizeof(device->model));
	DBG_DISC("DEV_TYPE: %x VENDOR: %s MODEL: %s\n",  device->devtype, device->vendor, device->model);

	if (pqisrc_is_logical_device(device) && device->devtype == DISK_DEVICE) {
		if (pqisrc_is_external_raid_device(device)) {
			device->raid_level = SA_RAID_UNKNOWN;
			device->volume_status = SA_LV_OK;
			device->volume_offline = false;
		} 
		else {
			pqisrc_get_dev_raid_level(softs, device);
			pqisrc_get_dev_ioaccel_status(softs, device);
			device->volume_status = pqisrc_get_dev_vol_status(softs,
						device->scsi3addr);
			device->volume_offline = device->volume_status != SA_LV_OK;
		}
	}

	/*
	 * Check if this is a One-Button-Disaster-Recovery device
	 * by looking for "$DR-10" at offset 43 in the inquiry data.
	 */
	device->is_obdr_device = (device->devtype == ROM_DEVICE &&
		memcmp(&inq_buff[OBDR_SIG_OFFSET], OBDR_TAPE_SIG,
			OBDR_SIG_LEN) == 0);
err_out:
	os_mem_free(softs, (char*)inq_buff, OBDR_TAPE_INQ_SIZE);

	DBG_FUNC("OUT\n");
	return ret;
}