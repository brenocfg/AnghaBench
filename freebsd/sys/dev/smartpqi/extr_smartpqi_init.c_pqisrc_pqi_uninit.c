#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int lockcreated; int /*<<< orphan*/  lock; } ;
struct TYPE_17__ {int devlist_lockcreated; int num_op_raid_ibq; int /*<<< orphan*/  admin_queue_dma_mem; TYPE_3__ admin_ib_queue; int /*<<< orphan*/  taglist; scalar_t__ max_outstanding_io; int /*<<< orphan*/  event_q_dma_mem; int /*<<< orphan*/  op_obq_dma_mem; int /*<<< orphan*/  op_ibq_dma_mem; TYPE_2__* op_aio_ib_q; TYPE_1__* op_raid_ib_q; int /*<<< orphan*/  devlist_lock; } ;
typedef  TYPE_4__ pqisrc_softstate_t ;
struct TYPE_15__ {int lockcreated; int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int lockcreated; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  OS_UNINIT_PQILOCK (int /*<<< orphan*/ *) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_complete_outstanding_cmds_nodevice (TYPE_4__*) ; 
 int /*<<< orphan*/  os_dma_mem_free (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_uninit_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_complete_internal_cmds (TYPE_4__*) ; 
 int /*<<< orphan*/  pqisrc_destroy_taglist (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ pqisrc_force_sis (TYPE_4__*) ; 
 int /*<<< orphan*/  pqisrc_free_rcb (TYPE_4__*,scalar_t__) ; 
 int pqisrc_wait_for_cmnd_complete (TYPE_4__*) ; 
 int /*<<< orphan*/  pqisrc_wait_for_rescan_complete (TYPE_4__*) ; 

void pqisrc_pqi_uninit(pqisrc_softstate_t *softs)
{
	int i, ret;

	DBG_FUNC("IN\n");
	
	/* Wait for any rescan to finish */
	pqisrc_wait_for_rescan_complete(softs);

	/* Wait for commands to complete */
	ret = pqisrc_wait_for_cmnd_complete(softs);
	
	/* Complete all pending commands. */
	if(ret != PQI_STATUS_SUCCESS) {
		pqisrc_complete_internal_cmds(softs);
		os_complete_outstanding_cmds_nodevice(softs);
	}

    if(softs->devlist_lockcreated==true){    
        os_uninit_spinlock(&softs->devlist_lock);
        softs->devlist_lockcreated = false;
    }
    
	for (i = 0; i <  softs->num_op_raid_ibq; i++) {
        /* OP RAID IB Q */
        if(softs->op_raid_ib_q[i].lockcreated==true){
		OS_UNINIT_PQILOCK(&softs->op_raid_ib_q[i].lock);
		softs->op_raid_ib_q[i].lockcreated = false;
        }
        
        /* OP AIO IB Q */
        if(softs->op_aio_ib_q[i].lockcreated==true){
		OS_UNINIT_PQILOCK(&softs->op_aio_ib_q[i].lock);
		softs->op_aio_ib_q[i].lockcreated = false;
        }
	}

	/* Free Op queues */
	os_dma_mem_free(softs, &softs->op_ibq_dma_mem);
	os_dma_mem_free(softs, &softs->op_obq_dma_mem);
	os_dma_mem_free(softs, &softs->event_q_dma_mem);
	
	/* Free  rcb */
	pqisrc_free_rcb(softs, softs->max_outstanding_io + 1);

	/* Free request id lists */
	pqisrc_destroy_taglist(softs,&softs->taglist);

	if(softs->admin_ib_queue.lockcreated==true){
		OS_UNINIT_PQILOCK(&softs->admin_ib_queue.lock);	
        	softs->admin_ib_queue.lockcreated = false;
	}

	/* Free Admin Queue */
	os_dma_mem_free(softs, &softs->admin_queue_dma_mem);

	/* Switch back to SIS mode */
	if (pqisrc_force_sis(softs)) {
		DBG_ERR("Failed to switch back the adapter to SIS mode!\n");
	}

	DBG_FUNC("OUT\n");
}