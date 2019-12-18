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
struct AdapterControlBlock {int /*<<< orphan*/  isr_lock; int /*<<< orphan*/  psim; int /*<<< orphan*/  ppath; int /*<<< orphan*/ ** sys_res_arcmsr; int /*<<< orphan*/ * rid; int /*<<< orphan*/  devmap_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_free_resource (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_mutex_destroy (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_teardown_intr (int /*<<< orphan*/ ,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arcmsr_detach(device_t dev)
{
	struct AdapterControlBlock *acb=(struct AdapterControlBlock *)device_get_softc(dev);
	int i;

	callout_stop(&acb->devmap_callout);
	arcmsr_teardown_intr(dev, acb);
	arcmsr_shutdown(dev);
	arcmsr_free_resource(acb);
	for(i=0; (acb->sys_res_arcmsr[i]!=NULL) && (i<2); i++) {
		bus_release_resource(dev, SYS_RES_MEMORY, acb->rid[i], acb->sys_res_arcmsr[i]);
	}
	ARCMSR_LOCK_ACQUIRE(&acb->isr_lock);
	xpt_async(AC_LOST_DEVICE, acb->ppath, NULL);
	xpt_free_path(acb->ppath);
	xpt_bus_deregister(cam_sim_path(acb->psim));
	cam_sim_free(acb->psim, TRUE);
	ARCMSR_LOCK_RELEASE(&acb->isr_lock);
	arcmsr_mutex_destroy(acb);
	return (0);
}