#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ index; } ;
struct cam_ed {scalar_t__ refcount; int flags; int /*<<< orphan*/  device_destroy_task; int /*<<< orphan*/  nvme_cdata; int /*<<< orphan*/  nvme_data; int /*<<< orphan*/  serial_num; int /*<<< orphan*/  rcap_buf; int /*<<< orphan*/  physpath; int /*<<< orphan*/  ext_inq; int /*<<< orphan*/  device_id; int /*<<< orphan*/  supported_vpds; int /*<<< orphan*/  ccbq; TYPE_5__* target; int /*<<< orphan*/  callout; TYPE_3__ devq_entry; int /*<<< orphan*/  periphs; } ;
struct cam_eb {TYPE_1__* sim; int /*<<< orphan*/  eb_mtx; } ;
struct TYPE_7__ {scalar_t__ array_size; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; TYPE_2__ send_queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  generation; int /*<<< orphan*/  ed_entries; struct cam_eb* bus; } ;
struct TYPE_9__ {int /*<<< orphan*/  xpt_taskq; } ;
struct TYPE_6__ {struct cam_devq* devq; } ;

/* Variables and functions */
 int CAM_DEV_REL_TIMEOUT_PENDING ; 
 scalar_t__ CAM_UNQUEUED_INDEX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_ccbq_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_devq_resize (struct cam_devq*,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_target (TYPE_5__*) ; 
 TYPE_4__ xsoftc ; 

void
xpt_release_device(struct cam_ed *device)
{
	struct cam_eb *bus = device->target->bus;
	struct cam_devq *devq;

	mtx_lock(&bus->eb_mtx);
	if (--device->refcount > 0) {
		mtx_unlock(&bus->eb_mtx);
		return;
	}

	TAILQ_REMOVE(&device->target->ed_entries, device,links);
	device->target->generation++;
	mtx_unlock(&bus->eb_mtx);

	/* Release our slot in the devq */
	devq = bus->sim->devq;
	mtx_lock(&devq->send_mtx);
	cam_devq_resize(devq, devq->send_queue.array_size - 1);
	mtx_unlock(&devq->send_mtx);

	KASSERT(SLIST_EMPTY(&device->periphs),
	    ("destroying device, but periphs list is not empty"));
	KASSERT(device->devq_entry.index == CAM_UNQUEUED_INDEX,
	    ("destroying device while still queued for ccbs"));

	if ((device->flags & CAM_DEV_REL_TIMEOUT_PENDING) != 0)
		callout_stop(&device->callout);

	xpt_release_target(device->target);

	cam_ccbq_fini(&device->ccbq);
	/*
	 * Free allocated memory.  free(9) does nothing if the
	 * supplied pointer is NULL, so it is safe to call without
	 * checking.
	 */
	free(device->supported_vpds, M_CAMXPT);
	free(device->device_id, M_CAMXPT);
	free(device->ext_inq, M_CAMXPT);
	free(device->physpath, M_CAMXPT);
	free(device->rcap_buf, M_CAMXPT);
	free(device->serial_num, M_CAMXPT);
	free(device->nvme_data, M_CAMXPT);
	free(device->nvme_cdata, M_CAMXPT);
	taskqueue_enqueue(xsoftc.xpt_taskq, &device->device_destroy_task);
}