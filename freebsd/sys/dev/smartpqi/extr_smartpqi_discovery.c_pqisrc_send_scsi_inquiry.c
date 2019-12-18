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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  raid_path_error_info_elem_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SA_INQUIRY ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pqisrc_build_send_raid_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqisrc_send_scsi_inquiry(pqisrc_softstate_t *softs,
	uint8_t *scsi3addr, uint16_t vpd_page, uint8_t *buff, int buf_len)
{
	int ret = PQI_STATUS_SUCCESS;
	pqisrc_raid_req_t request;
	raid_path_error_info_elem_t error_info;

	DBG_FUNC("IN\n");

	memset(&request, 0, sizeof(request));
	ret =  pqisrc_build_send_raid_request(softs, &request, buff, buf_len, 
								SA_INQUIRY, vpd_page, scsi3addr, &error_info);

	DBG_FUNC("OUT\n");
	return ret;
}