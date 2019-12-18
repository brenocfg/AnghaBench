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
typedef  int /*<<< orphan*/  ib_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int /*<<< orphan*/  PQI_CHANGE_OP_IQ_PROP_ASSIGN_AIO ; 
 int PQI_STATUS_SUCCESS ; 
 int pqisrc_change_op_ibq_queue_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pqisrc_create_op_ibq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pqisrc_create_op_aio_ibq(pqisrc_softstate_t *softs,
			ib_queue_t *op_aio_ib_q)
{
	int ret = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");
	
	ret = pqisrc_create_op_ibq(softs,op_aio_ib_q);
	if ( PQI_STATUS_SUCCESS == ret)
		ret = pqisrc_change_op_ibq_queue_prop(softs,
					op_aio_ib_q, PQI_CHANGE_OP_IQ_PROP_ASSIGN_AIO);

	DBG_FUNC("OUT ret : %d\n", ret);
	return ret;
}