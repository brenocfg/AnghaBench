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
typedef  int uint32_t ;
struct TYPE_5__ {int max_cmd_size; int max_fib_size; } ;
struct TYPE_6__ {TYPE_1__ pref_settings; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INIT (char*,int,int) ; 
 int PQI_STATUS_SUCCESS ; 
 int SIS_CMD_GET_COMM_PREFERRED_SETTINGS ; 
 int pqisrc_send_sis_cmd (TYPE_2__*,int*) ; 

int pqisrc_get_preferred_settings(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t mb[6] = {0};

	DBG_FUNC("IN\n");

	mb[0] = SIS_CMD_GET_COMM_PREFERRED_SETTINGS;
	ret = pqisrc_send_sis_cmd(softs, mb);
	if (!ret) {
		/* 31:16 maximum command size in KB */
		softs->pref_settings.max_cmd_size = mb[1] >> 16;
		/* 15:00: Maximum FIB size in bytes */
		softs->pref_settings.max_fib_size = mb[1] & 0x0000FFFF;
		DBG_INIT("cmd size = %x, fib size = %x\n",
			softs->pref_settings.max_cmd_size,
			softs->pref_settings.max_fib_size);
	}

	DBG_FUNC("OUT\n");
	return ret;
}