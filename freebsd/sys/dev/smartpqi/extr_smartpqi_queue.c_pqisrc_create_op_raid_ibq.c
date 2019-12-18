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
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_SUCCESS ; 
 int pqisrc_create_op_ibq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pqisrc_create_op_raid_ibq(pqisrc_softstate_t *softs,
			ib_queue_t *op_raid_ib_q)
{
	int ret = PQI_STATUS_SUCCESS;;
	
	DBG_FUNC("IN\n");
	
	ret = pqisrc_create_op_ibq(softs,op_raid_ib_q);
	
	DBG_FUNC("OUT\n");
	return ret;
}