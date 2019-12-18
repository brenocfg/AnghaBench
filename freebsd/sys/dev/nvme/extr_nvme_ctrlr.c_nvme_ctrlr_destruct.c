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
struct nvme_controller {int num_io_queues; int /*<<< orphan*/  lock; int /*<<< orphan*/ * resource; int /*<<< orphan*/  resource_id; int /*<<< orphan*/ * bar4_resource; int /*<<< orphan*/  bar4_resource_id; int /*<<< orphan*/ * res; int /*<<< orphan*/  dev; scalar_t__ tag; scalar_t__ taskqueue; int /*<<< orphan*/  adminq; int /*<<< orphan*/ * ioq; scalar_t__ is_initialized; scalar_t__ cdev; int /*<<< orphan*/ * ns; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NVME ; 
 int NVME_MAX_NAMESPACES ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  csts ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_admin_qpair_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ctrlr_delete_qpairs (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_disable (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_fail (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_shutdown (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_io_qpair_destroy (int /*<<< orphan*/ *) ; 
 int nvme_mmio_read_4 (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_notify_fail_consumers (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ns_destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (scalar_t__) ; 

void
nvme_ctrlr_destruct(struct nvme_controller *ctrlr, device_t dev)
{
	int	gone, i;

	if (ctrlr->resource == NULL)
		goto nores;

	/*
	 * Check whether it is a hot unplug or a clean driver detach.
	 * If device is not there any more, skip any shutdown commands.
	 */
	gone = (nvme_mmio_read_4(ctrlr, csts) == 0xffffffff);
	if (gone)
		nvme_ctrlr_fail(ctrlr);
	else
		nvme_notify_fail_consumers(ctrlr);

	for (i = 0; i < NVME_MAX_NAMESPACES; i++)
		nvme_ns_destruct(&ctrlr->ns[i]);

	if (ctrlr->cdev)
		destroy_dev(ctrlr->cdev);

	if (ctrlr->is_initialized) {
		if (!gone)
			nvme_ctrlr_delete_qpairs(ctrlr);
		for (i = 0; i < ctrlr->num_io_queues; i++)
			nvme_io_qpair_destroy(&ctrlr->ioq[i]);
		free(ctrlr->ioq, M_NVME);
		nvme_admin_qpair_destroy(&ctrlr->adminq);
	}

	/*
	 *  Notify the controller of a shutdown, even though this is due to
	 *   a driver unload, not a system shutdown (this path is not invoked
	 *   during shutdown).  This ensures the controller receives a
	 *   shutdown notification in case the system is shutdown before
	 *   reloading the driver.
	 */
	if (!gone)
		nvme_ctrlr_shutdown(ctrlr);

	if (!gone)
		nvme_ctrlr_disable(ctrlr);

	if (ctrlr->taskqueue)
		taskqueue_free(ctrlr->taskqueue);

	if (ctrlr->tag)
		bus_teardown_intr(ctrlr->dev, ctrlr->res, ctrlr->tag);

	if (ctrlr->res)
		bus_release_resource(ctrlr->dev, SYS_RES_IRQ,
		    rman_get_rid(ctrlr->res), ctrlr->res);

	if (ctrlr->bar4_resource != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    ctrlr->bar4_resource_id, ctrlr->bar4_resource);
	}

	bus_release_resource(dev, SYS_RES_MEMORY,
	    ctrlr->resource_id, ctrlr->resource);

nores:
	mtx_destroy(&ctrlr->lock);
}