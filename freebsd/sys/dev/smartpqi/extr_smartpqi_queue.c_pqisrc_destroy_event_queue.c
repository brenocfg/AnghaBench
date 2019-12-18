#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int created; int /*<<< orphan*/  q_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  event_q_dma_mem; TYPE_1__ event_q; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int pqisrc_delete_op_queue (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void pqisrc_destroy_event_queue(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN\n");

	if (softs->event_q.created == true) {
		int ret = PQI_STATUS_SUCCESS;
		ret = pqisrc_delete_op_queue(softs, softs->event_q.q_id, false);
		if (ret) {
			DBG_ERR("Failed to Delete Event Q %d\n", softs->event_q.q_id);
		}
		softs->event_q.created = false;
	}
	
	/* Free the memory */
	os_dma_mem_free(softs, &softs->event_q_dma_mem);

	DBG_FUNC("OUT\n");
}