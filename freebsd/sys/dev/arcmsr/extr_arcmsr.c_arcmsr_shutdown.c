#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct CommandControlBlock {scalar_t__ srb_state; TYPE_2__* pccb; } ;
struct AdapterControlBlock {scalar_t__ srboutstandingcount; int /*<<< orphan*/  isr_lock; scalar_t__ pktReturnCount; scalar_t__ pktRequestCount; scalar_t__ workingsrb_startindex; scalar_t__ workingsrb_doneindex; struct CommandControlBlock** psrb_pool; int /*<<< orphan*/  acb_flags; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_IOP_INITED ; 
 int /*<<< orphan*/  ACB_F_SCSISTOPADAPTER ; 
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 size_t ARCMSR_MAX_FREESRB_NUM ; 
 scalar_t__ ARCMSR_SRB_ABORTED ; 
 scalar_t__ ARCMSR_SRB_START ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  arcmsr_abort_allcmd (struct AdapterControlBlock*) ; 
 size_t arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_done4abort_postqueue (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_srb_complete (struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  arcmsr_stop_adapter_bgrb (struct AdapterControlBlock*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arcmsr_shutdown(device_t dev)
{
	u_int32_t  i;
	u_int32_t intmask_org;
	struct CommandControlBlock *srb;
	struct AdapterControlBlock *acb=(struct AdapterControlBlock *)device_get_softc(dev);

	/* stop adapter background rebuild */
	ARCMSR_LOCK_ACQUIRE(&acb->isr_lock);
	/* disable all outbound interrupt */
	intmask_org = arcmsr_disable_allintr(acb);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);
	/* abort all outstanding command */
	acb->acb_flags |= ACB_F_SCSISTOPADAPTER;
	acb->acb_flags &= ~ACB_F_IOP_INITED;
	if(acb->srboutstandingcount != 0) {
		/*clear and abort all outbound posted Q*/
		arcmsr_done4abort_postqueue(acb);
		/* talk to iop 331 outstanding command aborted*/
		arcmsr_abort_allcmd(acb);
		for(i=0; i < ARCMSR_MAX_FREESRB_NUM; i++) {
			srb = acb->psrb_pool[i];
			if(srb->srb_state == ARCMSR_SRB_START) {
				srb->srb_state = ARCMSR_SRB_ABORTED;
				srb->pccb->ccb_h.status |= CAM_REQ_ABORTED;
				arcmsr_srb_complete(srb, 1);
			}
		}
	}
	acb->srboutstandingcount = 0;
	acb->workingsrb_doneindex = 0;
	acb->workingsrb_startindex = 0;
	acb->pktRequestCount = 0;
	acb->pktReturnCount = 0;
	ARCMSR_LOCK_RELEASE(&acb->isr_lock);
	return (0);
}