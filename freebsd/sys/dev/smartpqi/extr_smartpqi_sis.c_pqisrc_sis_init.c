#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int pqi_reset_quiesce_allowed; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int SIS_SUPPORT_EXT_OPT ; 
 int SIS_SUPPORT_PQI ; 
 int SIS_SUPPORT_PQI_RESET_QUIESCE ; 
 int pqisrc_check_fw_status (TYPE_1__*) ; 
 int pqisrc_force_sis (TYPE_1__*) ; 
 int pqisrc_get_adapter_properties (TYPE_1__*,int*,int*) ; 
 int pqisrc_get_preferred_settings (TYPE_1__*) ; 
 int pqisrc_get_sis_pqi_cap (TYPE_1__*) ; 
 int pqisrc_init_struct_base (TYPE_1__*) ; 

int pqisrc_sis_init(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t prop = 0;
	uint32_t ext_prop = 0;

	DBG_FUNC("IN\n");

	ret = pqisrc_force_sis(softs);
	if (ret) {
		DBG_ERR("Failed to switch back the adapter to SIS mode!\n");
		goto err_out;
	}

	/* Check FW status ready	*/
	ret = pqisrc_check_fw_status(softs);
	if (ret) {
		DBG_ERR("PQI Controller is not ready !!!\n");
		goto err_out;
	}

	/* Check For PQI support(19h) */
	ret = pqisrc_get_adapter_properties(softs, &prop, &ext_prop);
	if (ret) {
		DBG_ERR("Failed to get adapter properties\n");
		goto err_out;
	}
	if (!((prop & SIS_SUPPORT_EXT_OPT) &&
		(ext_prop & SIS_SUPPORT_PQI))) {
		DBG_ERR("PQI Mode Not Supported\n");
		ret = PQI_STATUS_FAILURE;
		goto err_out;
	}

	softs->pqi_reset_quiesce_allowed = false;
	if (ext_prop & SIS_SUPPORT_PQI_RESET_QUIESCE)
		softs->pqi_reset_quiesce_allowed = true;

	/* Send GET_COMM_PREFERRED_SETTINGS (26h)  */
	ret = pqisrc_get_preferred_settings(softs);
	if (ret) {
		DBG_ERR("Failed to get adapter pref settings\n");
		goto err_out;
	}

	/* Get PQI settings , 3000h*/
	ret = pqisrc_get_sis_pqi_cap(softs);
	if (ret) {
		DBG_ERR("Failed to get PQI Capabilities\n");
		goto err_out;
	}

	/* Init struct base addr */
	ret = pqisrc_init_struct_base(softs);
	if (ret) {
		DBG_ERR("Failed to set init struct base addr\n");
		goto err_out;
	}

	DBG_FUNC("OUT\n");
	return ret;

err_out:
	DBG_FUNC("OUT failed\n");
	return ret;
}