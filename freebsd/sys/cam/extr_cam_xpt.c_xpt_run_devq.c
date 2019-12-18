#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  periph_data; } ;
struct TYPE_11__ {int flags; scalar_t__ func_code; TYPE_3__ qos; TYPE_6__* path; } ;
struct TYPE_8__ {scalar_t__ tag_action; } ;
union ccb {TYPE_4__ ccb_h; TYPE_1__ csio; } ;
struct xpt_proto {TYPE_2__* ops; } ;
struct mtx {int dummy; } ;
struct cam_sim {int /*<<< orphan*/  (* sim_action ) (struct cam_sim*,union ccb*) ;struct mtx* mtx; } ;
struct cam_ed {int inq_flags; struct cam_sim* sim; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ccbq; } ;
struct TYPE_14__ {int qfrozen_cnt; scalar_t__ entries; } ;
struct cam_devq {scalar_t__ send_openings; TYPE_7__ send_queue; struct mtx send_mtx; int /*<<< orphan*/  send_active; } ;
struct TYPE_13__ {struct cam_ed* device; } ;
struct TYPE_12__ {scalar_t__ num_highpower; struct mtx xpt_highpower_lock; int /*<<< orphan*/  highpowerq; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* debug_out ) (union ccb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAMQ_HEAD ; 
 int /*<<< orphan*/  CAM_DEBUG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_XPT ; 
 int CAM_DEV_QFREEZE ; 
 int CAM_HIGH_POWER ; 
 scalar_t__ CAM_TAG_ACTION_NONE ; 
 int CAM_TAG_ACTION_VALID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SID_CmdQue ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cam_ed*,int /*<<< orphan*/ ) ; 
 scalar_t__ XPT_SCSI_IO ; 
 union ccb* cam_ccbq_peek_ccb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_ccbq_remove_ccb (int /*<<< orphan*/ *,union ccb*) ; 
 int /*<<< orphan*/  cam_ccbq_send_ccb (int /*<<< orphan*/ *,union ccb*) ; 
 int /*<<< orphan*/  cam_iosched_now () ; 
 scalar_t__ camq_remove (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  highpowerq_entry ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_owned (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (union ccb*) ; 
 int /*<<< orphan*/  stub2 (struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (TYPE_6__*,int) ; 
 int /*<<< orphan*/  xpt_freeze_devq_device (struct cam_ed*,int) ; 
 struct xpt_proto* xpt_proto_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule_devq (struct cam_devq*,struct cam_ed*) ; 
 TYPE_5__ xsoftc ; 

__attribute__((used)) static void
xpt_run_devq(struct cam_devq *devq)
{
	struct mtx *mtx;

	CAM_DEBUG_PRINT(CAM_DEBUG_XPT, ("xpt_run_devq\n"));

	devq->send_queue.qfrozen_cnt++;
	while ((devq->send_queue.entries > 0)
	    && (devq->send_openings > 0)
	    && (devq->send_queue.qfrozen_cnt <= 1)) {
		struct	cam_ed *device;
		union ccb *work_ccb;
		struct	cam_sim *sim;
		struct xpt_proto *proto;

		device = (struct cam_ed *)camq_remove(&devq->send_queue,
							   CAMQ_HEAD);
		CAM_DEBUG_PRINT(CAM_DEBUG_XPT,
				("running device %p\n", device));

		work_ccb = cam_ccbq_peek_ccb(&device->ccbq, CAMQ_HEAD);
		if (work_ccb == NULL) {
			printf("device on run queue with no ccbs???\n");
			continue;
		}

		if ((work_ccb->ccb_h.flags & CAM_HIGH_POWER) != 0) {

			mtx_lock(&xsoftc.xpt_highpower_lock);
		 	if (xsoftc.num_highpower <= 0) {
				/*
				 * We got a high power command, but we
				 * don't have any available slots.  Freeze
				 * the device queue until we have a slot
				 * available.
				 */
				xpt_freeze_devq_device(device, 1);
				STAILQ_INSERT_TAIL(&xsoftc.highpowerq, device,
						   highpowerq_entry);

				mtx_unlock(&xsoftc.xpt_highpower_lock);
				continue;
			} else {
				/*
				 * Consume a high power slot while
				 * this ccb runs.
				 */
				xsoftc.num_highpower--;
			}
			mtx_unlock(&xsoftc.xpt_highpower_lock);
		}
		cam_ccbq_remove_ccb(&device->ccbq, work_ccb);
		cam_ccbq_send_ccb(&device->ccbq, work_ccb);
		devq->send_openings--;
		devq->send_active++;
		xpt_schedule_devq(devq, device);
		mtx_unlock(&devq->send_mtx);

		if ((work_ccb->ccb_h.flags & CAM_DEV_QFREEZE) != 0) {
			/*
			 * The client wants to freeze the queue
			 * after this CCB is sent.
			 */
			xpt_freeze_devq(work_ccb->ccb_h.path, 1);
		}

		/* In Target mode, the peripheral driver knows best... */
		if (work_ccb->ccb_h.func_code == XPT_SCSI_IO) {
			if ((device->inq_flags & SID_CmdQue) != 0
			 && work_ccb->csio.tag_action != CAM_TAG_ACTION_NONE)
				work_ccb->ccb_h.flags |= CAM_TAG_ACTION_VALID;
			else
				/*
				 * Clear this in case of a retried CCB that
				 * failed due to a rejected tag.
				 */
				work_ccb->ccb_h.flags &= ~CAM_TAG_ACTION_VALID;
		}

		KASSERT(device == work_ccb->ccb_h.path->device,
		    ("device (%p) / path->device (%p) mismatch",
			device, work_ccb->ccb_h.path->device));
		proto = xpt_proto_find(device->protocol);
		if (proto && proto->ops->debug_out)
			proto->ops->debug_out(work_ccb);

		/*
		 * Device queues can be shared among multiple SIM instances
		 * that reside on different buses.  Use the SIM from the
		 * queued device, rather than the one from the calling bus.
		 */
		sim = device->sim;
		mtx = sim->mtx;
		if (mtx && !mtx_owned(mtx))
			mtx_lock(mtx);
		else
			mtx = NULL;
		work_ccb->ccb_h.qos.periph_data = cam_iosched_now();
		(*(sim->sim_action))(sim, work_ccb);
		if (mtx)
			mtx_unlock(mtx);
		mtx_lock(&devq->send_mtx);
	}
	devq->send_queue.qfrozen_cnt--;
}