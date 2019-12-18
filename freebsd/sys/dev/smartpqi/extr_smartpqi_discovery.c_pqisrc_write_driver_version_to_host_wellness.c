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
struct bmic_host_wellness_driver_version {char* start_tag; char* driver_version_tag; char* driver_version; char* end_tag; int /*<<< orphan*/  driver_version_length; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_6__ {int /*<<< orphan*/  os_name; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_WRITE_HOST_WELLNESS ; 
 int /*<<< orphan*/  DBG_DISC (char*,int) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  LE_16 (int) ; 
 int /*<<< orphan*/  PQISRC_DRIVER_VERSION ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 scalar_t__ RAID_CTLR_LUNID ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct bmic_host_wellness_driver_version* os_mem_alloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  os_mem_free (TYPE_1__*,char*,size_t) ; 
 int pqisrc_build_send_raid_request (TYPE_1__*,int /*<<< orphan*/ *,struct bmic_host_wellness_driver_version*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int pqisrc_write_driver_version_to_host_wellness(pqisrc_softstate_t *softs)
{
	int rval = PQI_STATUS_SUCCESS;
	struct bmic_host_wellness_driver_version *host_wellness_driver_ver;
	size_t data_length;
	pqisrc_raid_req_t request;

	DBG_FUNC("IN\n");

	memset(&request, 0, sizeof(request));	
	data_length = sizeof(*host_wellness_driver_ver);

	host_wellness_driver_ver = os_mem_alloc(softs, data_length);
	if (!host_wellness_driver_ver) {
		DBG_ERR("failed to allocate memory for host wellness driver_version\n");
		return PQI_STATUS_FAILURE;
	}

	host_wellness_driver_ver->start_tag[0] = '<';
	host_wellness_driver_ver->start_tag[1] = 'H';
	host_wellness_driver_ver->start_tag[2] = 'W';
	host_wellness_driver_ver->start_tag[3] = '>';
	host_wellness_driver_ver->driver_version_tag[0] = 'D';
	host_wellness_driver_ver->driver_version_tag[1] = 'V';
	host_wellness_driver_ver->driver_version_length = LE_16(sizeof(host_wellness_driver_ver->driver_version));
	strncpy(host_wellness_driver_ver->driver_version, softs->os_name,
        sizeof(host_wellness_driver_ver->driver_version));
    if (strlen(softs->os_name) < sizeof(host_wellness_driver_ver->driver_version) ) {
        strncpy(host_wellness_driver_ver->driver_version + strlen(softs->os_name), PQISRC_DRIVER_VERSION,
			sizeof(host_wellness_driver_ver->driver_version) -  strlen(softs->os_name));
    } else {
        DBG_DISC("OS name length(%lu) is longer than buffer of driver_version\n",
            strlen(softs->os_name));
    }
	host_wellness_driver_ver->driver_version[sizeof(host_wellness_driver_ver->driver_version) - 1] = '\0';
	host_wellness_driver_ver->end_tag[0] = 'Z';
	host_wellness_driver_ver->end_tag[1] = 'Z';

	rval = pqisrc_build_send_raid_request(softs, &request, host_wellness_driver_ver,data_length,
					BMIC_WRITE_HOST_WELLNESS, 0, (uint8_t *)RAID_CTLR_LUNID, NULL);

	os_mem_free(softs, (char *)host_wellness_driver_ver, data_length);
	
	DBG_FUNC("OUT");
	return rval;
}