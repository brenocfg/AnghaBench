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
struct TYPE_5__ {int /*<<< orphan*/  admin_queue_dma_mem; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PQI_ADMIN_QUEUE_CONF_FUNC_DEL_Q_PAIR ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pqisrc_create_delete_adminq (TYPE_1__*,int /*<<< orphan*/ ) ; 

int pqisrc_destroy_admin_queue(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");
#if 0
	ret = pqisrc_create_delete_adminq(softs,
				PQI_ADMIN_QUEUE_CONF_FUNC_DEL_Q_PAIR);
#endif			
	os_dma_mem_free(softs, &softs->admin_queue_dma_mem);	
	
	DBG_FUNC("OUT\n");
	return ret;
}