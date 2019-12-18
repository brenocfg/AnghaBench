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
struct cam_et {int /*<<< orphan*/  generation; int /*<<< orphan*/  ed_entries; int /*<<< orphan*/  refcount; } ;
struct cam_ed {scalar_t__ lun_id; int refcount; int /*<<< orphan*/  device_destroy_task; int /*<<< orphan*/  callout; int /*<<< orphan*/  device_mtx; scalar_t__ tag_saved_openings; scalar_t__ tag_delay_count; int /*<<< orphan*/  flags; scalar_t__ generation; int /*<<< orphan*/  periphs; int /*<<< orphan*/  asyncs; int /*<<< orphan*/  ccbq; TYPE_2__* sim; struct cam_et* target; int /*<<< orphan*/  devq_entry; } ;
struct cam_eb {TYPE_2__* sim; int /*<<< orphan*/  eb_mtx; } ;
struct TYPE_3__ {scalar_t__ array_size; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; TYPE_1__ send_queue; } ;
typedef  scalar_t__ lun_id_t ;
typedef  scalar_t__ cam_status ;
struct TYPE_4__ {int /*<<< orphan*/  max_dev_openings; struct cam_devq* devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_UNCONFIGURED ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CAMDEV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 struct cam_ed* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct cam_ed*,struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cam_ed*,int /*<<< orphan*/ ) ; 
 struct cam_ed* TAILQ_NEXT (struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_ed*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_ccbq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_devq_resize (struct cam_devq*,scalar_t__) ; 
 int /*<<< orphan*/  cam_init_pinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_destroy_device ; 

struct cam_ed *
xpt_alloc_device(struct cam_eb *bus, struct cam_et *target, lun_id_t lun_id)
{
	struct cam_ed	*cur_device, *device;
	struct cam_devq	*devq;
	cam_status status;

	mtx_assert(&bus->eb_mtx, MA_OWNED);
	/* Make space for us in the device queue on our bus */
	devq = bus->sim->devq;
	mtx_lock(&devq->send_mtx);
	status = cam_devq_resize(devq, devq->send_queue.array_size + 1);
	mtx_unlock(&devq->send_mtx);
	if (status != CAM_REQ_CMP)
		return (NULL);

	device = (struct cam_ed *)malloc(sizeof(*device),
					 M_CAMDEV, M_NOWAIT|M_ZERO);
	if (device == NULL)
		return (NULL);

	cam_init_pinfo(&device->devq_entry);
	device->target = target;
	device->lun_id = lun_id;
	device->sim = bus->sim;
	if (cam_ccbq_init(&device->ccbq,
			  bus->sim->max_dev_openings) != 0) {
		free(device, M_CAMDEV);
		return (NULL);
	}
	SLIST_INIT(&device->asyncs);
	SLIST_INIT(&device->periphs);
	device->generation = 0;
	device->flags = CAM_DEV_UNCONFIGURED;
	device->tag_delay_count = 0;
	device->tag_saved_openings = 0;
	device->refcount = 1;
	mtx_init(&device->device_mtx, "CAM device lock", NULL, MTX_DEF);
	callout_init_mtx(&device->callout, &devq->send_mtx, 0);
	TASK_INIT(&device->device_destroy_task, 0, xpt_destroy_device, device);
	/*
	 * Hold a reference to our parent bus so it
	 * will not go away before we do.
	 */
	target->refcount++;

	cur_device = TAILQ_FIRST(&target->ed_entries);
	while (cur_device != NULL && cur_device->lun_id < lun_id)
		cur_device = TAILQ_NEXT(cur_device, links);
	if (cur_device != NULL)
		TAILQ_INSERT_BEFORE(cur_device, device, links);
	else
		TAILQ_INSERT_TAIL(&target->ed_entries, device, links);
	target->generation++;
	return (device);
}