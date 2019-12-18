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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SIS_CMD_GET_ADAPTER_PROPERTIES ; 
 int pqisrc_send_sis_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pqisrc_get_adapter_properties(pqisrc_softstate_t *softs,
				uint32_t *prop, uint32_t *ext_prop)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t mb[6] = {0};

	DBG_FUNC("IN\n");

	mb[0] = SIS_CMD_GET_ADAPTER_PROPERTIES;
	ret = pqisrc_send_sis_cmd(softs, mb);
	if (!ret) {
		DBG_INIT("GET_PROPERTIES prop = %x, ext_prop = %x\n",
					mb[1], mb[4]);
		*prop = mb[1];
		*ext_prop = mb[4];
	}

	DBG_FUNC("OUT\n");
	return ret;
}