#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 scalar_t__ SA_LV_STATUS_VPD_UNSUPPORTED ; 
 int SA_VPD_LV_STATUS ; 
 scalar_t__ SCSI_VPD_HEADER_LENGTH ; 
 int VPD_PAGE ; 
 scalar_t__* os_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,char*,int) ; 
 int pqisrc_send_scsi_inquiry (int /*<<< orphan*/ *,scalar_t__*,int,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static uint8_t pqisrc_get_volume_offline_status(pqisrc_softstate_t *softs,
	uint8_t *scsi3addr)
{
	int ret = PQI_STATUS_SUCCESS;
	uint8_t status = SA_LV_STATUS_VPD_UNSUPPORTED;
	uint8_t size;
	uint8_t *buff = NULL;

	DBG_FUNC("IN\n");
	
	buff = os_mem_alloc(softs, 64);
	if (!buff)
		return PQI_STATUS_FAILURE;

	/* Get the size of the VPD return buff. */
	ret = pqisrc_send_scsi_inquiry(softs, scsi3addr, VPD_PAGE | SA_VPD_LV_STATUS,
		buff, SCSI_VPD_HEADER_LENGTH);

	if (ret)
		goto out;

	size = buff[3];

	/* Now get the whole VPD buff. */
	ret = pqisrc_send_scsi_inquiry(softs, scsi3addr, VPD_PAGE | SA_VPD_LV_STATUS,
		buff, size + SCSI_VPD_HEADER_LENGTH);
	if (ret)
		goto out;

	status = buff[4];

out:
	os_mem_free(softs, (char *)buff, 64);
	DBG_FUNC("OUT\n");

	return status;
}