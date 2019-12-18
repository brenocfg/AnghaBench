#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* pqi_irq_rid; void** intr_registered; int /*<<< orphan*/ * intrcookie; TYPE_4__* msi_ctx; int /*<<< orphan*/ ** pqi_irq; void* pqi_dev; } ;
struct TYPE_8__ {int intr_count; TYPE_1__ os_specific; scalar_t__ share_opq_and_eventq; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  pqi_intr_ctx_t ;
typedef  void* device_t ;
struct TYPE_9__ {int oq_id; void* pqi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int PQI_STATUS_FAILURE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* TRUE ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_ithread_routine ; 
 int /*<<< orphan*/  event_ithread_routine ; 
 TYPE_4__* os_mem_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  shared_ithread_routine ; 

int register_msix_intr(pqisrc_softstate_t *softs)
{
	int error = 0;
	int i = 0;
	device_t dev;
	dev = softs->os_specific.pqi_dev;
	int msix_count = softs->intr_count;

	DBG_FUNC("IN\n");

	softs->os_specific.msi_ctx = os_mem_alloc(softs, sizeof(pqi_intr_ctx_t) * msix_count);
	/*Add shared handler */
	if (softs->share_opq_and_eventq) {
		softs->os_specific.pqi_irq_rid[i] = i+1;
		softs->os_specific.pqi_irq[i] = bus_alloc_resource_any(dev, \
						SYS_RES_IRQ,
						&softs->os_specific.pqi_irq_rid[i],
						RF_SHAREABLE |  RF_ACTIVE);
		if (NULL == softs->os_specific.pqi_irq[i]) {
			DBG_ERR("Failed to allocate \
				event interrupt resource\n");
			return PQI_STATUS_FAILURE;
		}
				
		softs->os_specific.msi_ctx[i].pqi_dev = dev;
		softs->os_specific.msi_ctx[i].oq_id = i+1;
		
		error = bus_setup_intr(dev,softs->os_specific.pqi_irq[i],
					INTR_TYPE_CAM | INTR_MPSAFE,\
					NULL,
					shared_ithread_routine,
					&softs->os_specific.msi_ctx[i],
					&softs->os_specific.intrcookie[i]);

		if (error) {
			DBG_ERR("Failed to setup interrupt for events r=%d\n", 
				error);
			return error;
		}
		softs->os_specific.intr_registered[i] = TRUE;
	}
	else {
		/* Add event handler */
		softs->os_specific.pqi_irq_rid[i] = i+1;
		softs->os_specific.pqi_irq[i] = bus_alloc_resource_any(dev, \
						SYS_RES_IRQ,
						&softs->os_specific.pqi_irq_rid[i],
						RF_SHAREABLE |  RF_ACTIVE);
		if (NULL == softs->os_specific.pqi_irq[i]) {
			DBG_ERR("ERR : Failed to allocate \
				event interrupt resource\n");
			return PQI_STATUS_FAILURE;
		}
		
		
		softs->os_specific.msi_ctx[i].pqi_dev = dev;
		softs->os_specific.msi_ctx[i].oq_id = i;
		

		error = bus_setup_intr(dev,softs->os_specific.pqi_irq[i],
					INTR_TYPE_CAM | INTR_MPSAFE,\
                       			NULL,
					event_ithread_routine,
					&softs->os_specific.msi_ctx[i],
					&softs->os_specific.intrcookie[i]);
		if (error) {
			DBG_ERR("Failed to setup interrupt for events err=%d\n",
				error);
			return error;
		}
		softs->os_specific.intr_registered[i] = TRUE;
		/* Add interrupt handlers*/	
		for (i = 1; i < msix_count; ++i) {
			softs->os_specific.pqi_irq_rid[i] = i+1;
			softs->os_specific.pqi_irq[i] = \
					bus_alloc_resource_any(dev,
					SYS_RES_IRQ,
					&softs->os_specific.pqi_irq_rid[i],
					RF_SHAREABLE | RF_ACTIVE);
			if (NULL == softs->os_specific.pqi_irq[i]) {
				DBG_ERR("Failed to allocate \
					msi/x interrupt resource\n");
				return PQI_STATUS_FAILURE;
			}
			softs->os_specific.msi_ctx[i].pqi_dev = dev;
			softs->os_specific.msi_ctx[i].oq_id = i;
			error = bus_setup_intr(dev,
					softs->os_specific.pqi_irq[i],
					INTR_TYPE_CAM | INTR_MPSAFE,\
					NULL,
					common_ithread_routine,
					&softs->os_specific.msi_ctx[i],
					&softs->os_specific.intrcookie[i]);
			if (error) {
				DBG_ERR("Failed to setup \
					msi/x interrupt error = %d\n", error);
				return error;
			}
			softs->os_specific.intr_registered[i] = TRUE;
		}
	}

	DBG_FUNC("OUT error = %d\n", error);

	return error;
}