#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fw_build_number; char* fw_version; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
struct TYPE_11__ {int fw_build_number; int /*<<< orphan*/  fw_version; } ;
typedef  TYPE_2__ bmic_ident_ctrl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,char*,int) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* os_mem_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_mem_free (TYPE_1__*,char*,int) ; 
 int pqisrc_identify_ctrl (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

int pqisrc_get_ctrl_fw_version(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	bmic_ident_ctrl_t *identify_ctrl;

	DBG_FUNC("IN\n");

	identify_ctrl = os_mem_alloc(softs, sizeof(*identify_ctrl));
	if (!identify_ctrl) {
		DBG_ERR("failed to allocate memory for identify_ctrl\n");
		return PQI_STATUS_FAILURE;
	}

	memset(identify_ctrl, 0, sizeof(*identify_ctrl));

	ret = pqisrc_identify_ctrl(softs, identify_ctrl);
	if (ret)
		goto out;
     
	softs->fw_build_number = identify_ctrl->fw_build_number;
	memcpy(softs->fw_version, identify_ctrl->fw_version,
		sizeof(identify_ctrl->fw_version));
	softs->fw_version[sizeof(identify_ctrl->fw_version)] = '\0';
	snprintf(softs->fw_version +
		strlen(softs->fw_version),
		sizeof(softs->fw_version),
		"-%u", identify_ctrl->fw_build_number);
out:
	os_mem_free(softs, (char *)identify_ctrl, sizeof(*identify_ctrl));
	DBG_INIT("Firmware version: %s Firmware build number: %d\n", softs->fw_version, softs->fw_build_number);
	DBG_FUNC("OUT\n");
	return ret;
}