#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_5__ {void* max_outstanding_io; void* max_transfer_size; void* max_sg_elem; void* conf_tab_sz; void* conf_tab_off; } ;
struct TYPE_6__ {TYPE_1__ pqi_cap; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,void*) ; 
 int PQI_STATUS_SUCCESS ; 
 void* SIS_CMD_GET_PQI_CAPABILITIES ; 
 int pqisrc_send_sis_cmd (TYPE_2__*,void**) ; 

int pqisrc_get_sis_pqi_cap(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t mb[6] = {0};

	DBG_FUNC("IN\n");

	mb[0] = SIS_CMD_GET_PQI_CAPABILITIES;
	ret = pqisrc_send_sis_cmd(softs,  mb);
	if (!ret) {
		softs->pqi_cap.max_sg_elem = mb[1];
		softs->pqi_cap.max_transfer_size = mb[2];
		softs->pqi_cap.max_outstanding_io = mb[3];
		softs->pqi_cap.conf_tab_off = mb[4];
		softs->pqi_cap.conf_tab_sz =  mb[5];

		DBG_INIT("max_sg_elem = %x\n",
					softs->pqi_cap.max_sg_elem);
		DBG_INIT("max_transfer_size = %x\n",
					softs->pqi_cap.max_transfer_size);
		DBG_INIT("max_outstanding_io = %x\n",
					softs->pqi_cap.max_outstanding_io);
	}

	DBG_FUNC("OUT\n");
	return ret;
}