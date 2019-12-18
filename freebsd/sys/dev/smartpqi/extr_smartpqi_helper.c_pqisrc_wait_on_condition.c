#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int req_pending; } ;
typedef  TYPE_1__ rcb_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  IS_POLLING_REQUIRED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_SLEEP (int) ; 
 scalar_t__ PQISRC_CMD_TIMEOUT_CNT ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int PQI_STATUS_TIMEOUT ; 
 scalar_t__ pqisrc_ctrl_offline (int /*<<< orphan*/ *) ; 

int pqisrc_wait_on_condition(pqisrc_softstate_t *softs, rcb_t *rcb){

	DBG_FUNC("IN\n");

	int ret = PQI_STATUS_SUCCESS;
	uint32_t loop_cnt = 0;
	
	while (rcb->req_pending == true) {
		OS_SLEEP(500); /* Micro sec */

		/*Polling needed for FreeBSD : since ithread routine is not scheduled
                during bootup, we could use polling until interrupts are
                enabled (using 'if (cold)'to check for the boot time before
                interrupts are enabled). */
		IS_POLLING_REQUIRED(softs);

		if (loop_cnt++ == PQISRC_CMD_TIMEOUT_CNT) {
			DBG_ERR("ERR: Requested cmd timed out !!!\n");
			ret = PQI_STATUS_TIMEOUT;
			break;
		}
	
		if (pqisrc_ctrl_offline(softs)) {
			DBG_ERR("Controller is Offline");
			ret = PQI_STATUS_FAILURE;
			break;
		}

	}
	rcb->req_pending = true;

	DBG_FUNC("OUT\n");

	return ret;
}