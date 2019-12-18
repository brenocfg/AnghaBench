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
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int pqisrc_alloc_and_create_event_queue (int /*<<< orphan*/ *) ; 
 int pqisrc_alloc_and_create_ib_queues (int /*<<< orphan*/ *) ; 
 int pqisrc_alloc_and_create_ob_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_destroy_op_ib_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_destroy_op_ob_queues (int /*<<< orphan*/ *) ; 

int pqisrc_create_op_queues(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");
		
	/* Create Operational IB queues */
	ret = pqisrc_alloc_and_create_ib_queues(softs);
	if (ret)
		goto err_out;
	/* Create Operational OB queues */
	ret = pqisrc_alloc_and_create_ob_queues(softs);
	if (ret)
		goto err_out_obq;

	/* Create Event queue */
	ret = pqisrc_alloc_and_create_event_queue(softs);
	if (ret)
		goto err_out_eventq;		

	DBG_FUNC("OUT\n");
	return ret;
err_out_eventq:
	pqisrc_destroy_op_ob_queues(softs);	
err_out_obq:
	pqisrc_destroy_op_ib_queues(softs);
err_out:
	DBG_FUNC("OUT failed %d\n", ret);
	return PQI_STATUS_FAILURE;
}