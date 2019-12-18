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
 int /*<<< orphan*/  COND_WAIT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int GET_FW_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_SLEEP (int) ; 
 int PQI_CTRL_KERNEL_UP_AND_RUNNING ; 
 int PQI_STATUS_SUCCESS ; 
 int PQI_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  SIS_STATUS_OK_TIMEOUT ; 

int pqisrc_check_fw_status(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t timeout = SIS_STATUS_OK_TIMEOUT;

	DBG_FUNC("IN\n");

	OS_SLEEP(1000000);
	COND_WAIT((GET_FW_STATUS(softs) &
		PQI_CTRL_KERNEL_UP_AND_RUNNING), timeout);
	if (!timeout) {
		DBG_ERR("FW check status timedout\n");
		ret = PQI_STATUS_TIMEOUT;
	}

	DBG_FUNC("OUT\n");
	return ret;
}