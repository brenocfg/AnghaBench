#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ max_outstanding_io; scalar_t__ max_io_for_scsi_ml; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ PQI_RESERVED_IO_SLOTS_CNT ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  pqisrc_decide_opq_config (TYPE_1__*) ; 
 int pqisrc_report_pqi_capability (TYPE_1__*) ; 

int pqisrc_configure_op_queues(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	
	/* Get the PQI capability, 
		REPORT PQI DEVICE CAPABILITY request */
	ret = pqisrc_report_pqi_capability(softs);
	if (ret) {
		DBG_ERR("Failed to send report pqi dev capability request : %d\n",
				ret);
		goto err_out;
	}

	/* Reserve required no of slots for internal requests */
	softs->max_io_for_scsi_ml = softs->max_outstanding_io - PQI_RESERVED_IO_SLOTS_CNT;

	/* Decide the Op queue configuration */
	pqisrc_decide_opq_config(softs);	
	
	DBG_FUNC("OUT\n");
	return ret;
		
err_out:
	DBG_FUNC("OUT failed\n");
	return ret;
}