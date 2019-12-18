#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int ctrl_in_pqi_mode; scalar_t__ intr_type; int ctrl_online; scalar_t__ max_outstanding_io; int /*<<< orphan*/  taglist; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_PQI_MODE ; 
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ INTR_TYPE_FIXED ; 
 scalar_t__ INTR_TYPE_NONE ; 
 int /*<<< orphan*/  PQI_SAVE_CTRL_MODE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_free_intr_config (TYPE_1__*) ; 
 int os_get_intr_config (TYPE_1__*) ; 
 int os_get_processor_config (TYPE_1__*) ; 
 int pqisrc_allocate_rcb (TYPE_1__*) ; 
 int pqisrc_check_pqimode (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_configure_legacy_intx (TYPE_1__*,int) ; 
 int pqisrc_configure_op_queues (TYPE_1__*) ; 
 int pqisrc_create_admin_queue (TYPE_1__*) ; 
 int pqisrc_create_op_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_destroy_admin_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_destroy_taglist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_free_rcb (TYPE_1__*,scalar_t__) ; 
 int pqisrc_init_taglist (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sis_enable_intx (TYPE_1__*) ; 

int pqisrc_pqi_init(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");

	/* Check the PQI signature */
	ret = pqisrc_check_pqimode(softs);
	if(ret) {
		DBG_ERR("failed to switch to pqi\n");
                goto err_out;
	}

	PQI_SAVE_CTRL_MODE(softs, CTRL_PQI_MODE);
	softs->ctrl_in_pqi_mode = true;
	
	/* Get the No. of Online CPUs,NUMA/Processor config from OS */
	ret = os_get_processor_config(softs);
	if (ret) {
		DBG_ERR("Failed to get processor config from OS %d\n",
			ret);
		goto err_out;
	}
	
	softs->intr_type = INTR_TYPE_NONE;	

	/* Get the interrupt count, type, priority available from OS */
	ret = os_get_intr_config(softs);
	if (ret) {
		DBG_ERR("Failed to get interrupt config from OS %d\n",
			ret);
		goto err_out;
	}

	/*Enable/Set Legacy INTx Interrupt mask clear pqi register,
	 *if allocated interrupt is legacy type.
	 */
	if (INTR_TYPE_FIXED == softs->intr_type) {
		pqisrc_configure_legacy_intx(softs, true);
		sis_enable_intx(softs);
	}

	/* Create Admin Queue pair*/		
	ret = pqisrc_create_admin_queue(softs);
	if(ret) {
                DBG_ERR("Failed to configure admin queue\n");
                goto err_admin_queue;
    	}

	/* For creating event and IO operational queues we have to submit 
	   admin IU requests.So Allocate resources for submitting IUs */  
	     
	/* Allocate the request container block (rcb) */
	ret = pqisrc_allocate_rcb(softs);
	if (ret == PQI_STATUS_FAILURE) {
                DBG_ERR("Failed to allocate rcb \n");
                goto err_rcb;
    	}

	/* Allocate & initialize request id queue */
	ret = pqisrc_init_taglist(softs,&softs->taglist,
				softs->max_outstanding_io);
	if (ret) {
		DBG_ERR("Failed to allocate memory for request id q : %d\n",
			ret);
		goto err_taglist;
	}

	ret = pqisrc_configure_op_queues(softs);
	if (ret) {
			DBG_ERR("Failed to configure op queue\n");
			goto err_config_opq;
	}

	/* Create Operational queues */
	ret = pqisrc_create_op_queues(softs);
	if(ret) {
                DBG_ERR("Failed to create op queue\n");
                ret = PQI_STATUS_FAILURE;
                goto err_create_opq;
        }

	softs->ctrl_online = true;

	DBG_FUNC("OUT\n");
	return ret;

err_create_opq:
err_config_opq:
	pqisrc_destroy_taglist(softs,&softs->taglist);
err_taglist:
	pqisrc_free_rcb(softs, softs->max_outstanding_io + 1);		
err_rcb:
	pqisrc_destroy_admin_queue(softs);
err_admin_queue:
	os_free_intr_config(softs);
err_out:
	DBG_FUNC("OUT failed\n");
	return PQI_STATUS_FAILURE;
}