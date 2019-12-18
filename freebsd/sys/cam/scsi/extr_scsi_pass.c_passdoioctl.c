#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int xpt_opcode ;
struct TYPE_9__ {int /*<<< orphan*/  priority; } ;
struct TYPE_11__ {int func_code; int flags; int /*<<< orphan*/  periph_priv; int /*<<< orphan*/  periph_links; int /*<<< orphan*/  cbfcnp; TYPE_3__ pinfo; struct pass_io_req* ccb_ioreq; } ;
struct TYPE_7__ {union ccb* cdb_bytes; union ccb* cdb_ptr; } ;
struct TYPE_10__ {int cdb_len; TYPE_1__ cdb_io; int /*<<< orphan*/ * bio; } ;
union ccb {TYPE_5__ ccb_h; TYPE_4__ csio; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct pass_softc {int flags; int /*<<< orphan*/  pass_zone; int /*<<< orphan*/  done_queue; int /*<<< orphan*/  active_queue; int /*<<< orphan*/  incoming_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_bufs_used; } ;
struct pass_io_req {union ccb ccb; int /*<<< orphan*/  user_periph_priv; int /*<<< orphan*/  user_periph_links; TYPE_2__ mapinfo; union ccb* user_ccb_ptr; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CAMIOCOMMAND 130 
#define  CAMIOGET 129 
#define  CAMIOQUEUE 128 
 int CAM_CDB_POINTER ; 
 int /*<<< orphan*/  CAM_PRIORITY_OOB ; 
 int CAM_UNLOCKED ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int IOCDBLEN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PASS_FLAG_ZONE_VALID ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 int /*<<< orphan*/  SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pass_io_req* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pass_io_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pass_io_req*,int /*<<< orphan*/ ) ; 
 int XPT_ATA_IO ; 
 int XPT_DEV_ADVINFO ; 
 int XPT_DEV_MATCH ; 
 int XPT_FC_QUEUED ; 
 int XPT_FC_USER_CCB ; 
 int XPT_FC_XPT_ONLY ; 
 int XPT_NVME_ADMIN ; 
 int XPT_NVME_IO ; 
 int XPT_SCSI_IO ; 
 int XPT_SMP_IO ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int cam_periph_ioctl (struct cam_periph*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int copyin (union ccb*,union ccb*,int) ; 
 int copyout (union ccb*,union ccb*,int) ; 
 int /*<<< orphan*/  links ; 
 int passcreatezone (struct cam_periph*) ; 
 int /*<<< orphan*/  passdone ; 
 int /*<<< orphan*/  passerror ; 
 int passmemdone (struct cam_periph*,struct pass_io_req*) ; 
 int passmemsetup (struct cam_periph*,struct pass_io_req*) ; 
 int passsendccb (struct cam_periph*,union ccb*,union ccb*) ; 
 struct pass_io_req* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pass_io_req*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb_flags (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
passdoioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag, struct thread *td)
{
	struct	cam_periph *periph;
	struct	pass_softc *softc;
	int	error;
	uint32_t priority;

	periph = (struct cam_periph *)dev->si_drv1;
	cam_periph_lock(periph);
	softc = (struct pass_softc *)periph->softc;

	error = 0;

	switch (cmd) {

	case CAMIOCOMMAND:
	{
		union ccb *inccb;
		union ccb *ccb;
		int ccb_malloced;

		inccb = (union ccb *)addr;
#if defined(BUF_TRACKING) || defined(FULL_BUF_TRACKING)
		if (inccb->ccb_h.func_code == XPT_SCSI_IO)
			inccb->csio.bio = NULL;
#endif

		if (inccb->ccb_h.flags & CAM_UNLOCKED) {
			error = EINVAL;
			break;
		}

		/*
		 * Some CCB types, like scan bus and scan lun can only go
		 * through the transport layer device.
		 */
		if (inccb->ccb_h.func_code & XPT_FC_XPT_ONLY) {
			xpt_print(periph->path, "CCB function code %#x is "
			    "restricted to the XPT device\n",
			    inccb->ccb_h.func_code);
			error = ENODEV;
			break;
		}

		/* Compatibility for RL/priority-unaware code. */
		priority = inccb->ccb_h.pinfo.priority;
		if (priority <= CAM_PRIORITY_OOB)
		    priority += CAM_PRIORITY_OOB + 1;

		/*
		 * Non-immediate CCBs need a CCB from the per-device pool
		 * of CCBs, which is scheduled by the transport layer.
		 * Immediate CCBs and user-supplied CCBs should just be
		 * malloced.
		 */
		if ((inccb->ccb_h.func_code & XPT_FC_QUEUED)
		 && ((inccb->ccb_h.func_code & XPT_FC_USER_CCB) == 0)) {
			ccb = cam_periph_getccb(periph, priority);
			ccb_malloced = 0;
		} else {
			ccb = xpt_alloc_ccb_nowait();

			if (ccb != NULL)
				xpt_setup_ccb(&ccb->ccb_h, periph->path,
					      priority);
			ccb_malloced = 1;
		}

		if (ccb == NULL) {
			xpt_print(periph->path, "unable to allocate CCB\n");
			error = ENOMEM;
			break;
		}

		error = passsendccb(periph, ccb, inccb);

		if (ccb_malloced)
			xpt_free_ccb(ccb);
		else
			xpt_release_ccb(ccb);

		break;
	}
	case CAMIOQUEUE:
	{
		struct pass_io_req *io_req;
		union ccb **user_ccb, *ccb;
		xpt_opcode fc;

#ifdef COMPAT_FREEBSD32
		if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
			error = ENOTTY;
			goto bailout;
		}
#endif
		if ((softc->flags & PASS_FLAG_ZONE_VALID) == 0) {
			error = passcreatezone(periph);
			if (error != 0)
				goto bailout;
		}

		/*
		 * We're going to do a blocking allocation for this I/O
		 * request, so we have to drop the lock.
		 */
		cam_periph_unlock(periph);

		io_req = uma_zalloc(softc->pass_zone, M_WAITOK | M_ZERO);
		ccb = &io_req->ccb;
		user_ccb = (union ccb **)addr;

		/*
		 * Unlike the CAMIOCOMMAND ioctl above, we only have a
		 * pointer to the user's CCB, so we have to copy the whole
		 * thing in to a buffer we have allocated (above) instead
		 * of allowing the ioctl code to malloc a buffer and copy
		 * it in.
		 *
		 * This is an advantage for this asynchronous interface,
		 * since we don't want the memory to get freed while the
		 * CCB is outstanding.
		 */
#if 0
		xpt_print(periph->path, "Copying user CCB %p to "
			  "kernel address %p\n", *user_ccb, ccb);
#endif
		error = copyin(*user_ccb, ccb, sizeof(*ccb));
		if (error != 0) {
			xpt_print(periph->path, "Copy of user CCB %p to "
				  "kernel address %p failed with error %d\n",
				  *user_ccb, ccb, error);
			goto camioqueue_error;
		}
#if defined(BUF_TRACKING) || defined(FULL_BUF_TRACKING)
		if (ccb->ccb_h.func_code == XPT_SCSI_IO)
			ccb->csio.bio = NULL;
#endif

		if (ccb->ccb_h.flags & CAM_UNLOCKED) {
			error = EINVAL;
			goto camioqueue_error;
		}

		if (ccb->ccb_h.flags & CAM_CDB_POINTER) {
			if (ccb->csio.cdb_len > IOCDBLEN) {
				error = EINVAL;
				goto camioqueue_error;
			}
			error = copyin(ccb->csio.cdb_io.cdb_ptr,
			    ccb->csio.cdb_io.cdb_bytes, ccb->csio.cdb_len);
			if (error != 0)
				goto camioqueue_error;
			ccb->ccb_h.flags &= ~CAM_CDB_POINTER;
		}

		/*
		 * Some CCB types, like scan bus and scan lun can only go
		 * through the transport layer device.
		 */
		if (ccb->ccb_h.func_code & XPT_FC_XPT_ONLY) {
			xpt_print(periph->path, "CCB function code %#x is "
			    "restricted to the XPT device\n",
			    ccb->ccb_h.func_code);
			error = ENODEV;
			goto camioqueue_error;
		}

		/*
		 * Save the user's CCB pointer as well as his linked list
		 * pointers and peripheral private area so that we can
		 * restore these later.
		 */
		io_req->user_ccb_ptr = *user_ccb;
		io_req->user_periph_links = ccb->ccb_h.periph_links;
		io_req->user_periph_priv = ccb->ccb_h.periph_priv;

		/*
		 * Now that we've saved the user's values, we can set our
		 * own peripheral private entry.
		 */
		ccb->ccb_h.ccb_ioreq = io_req;

		/* Compatibility for RL/priority-unaware code. */
		priority = ccb->ccb_h.pinfo.priority;
		if (priority <= CAM_PRIORITY_OOB)
		    priority += CAM_PRIORITY_OOB + 1;

		/*
		 * Setup fields in the CCB like the path and the priority.
		 * The path in particular cannot be done in userland, since
		 * it is a pointer to a kernel data structure.
		 */
		xpt_setup_ccb_flags(&ccb->ccb_h, periph->path, priority,
				    ccb->ccb_h.flags);

		/*
		 * Setup our done routine.  There is no way for the user to
		 * have a valid pointer here.
		 */
		ccb->ccb_h.cbfcnp = passdone;

		fc = ccb->ccb_h.func_code;
		/*
		 * If this function code has memory that can be mapped in
		 * or out, we need to call passmemsetup().
		 */
		if ((fc == XPT_SCSI_IO) || (fc == XPT_ATA_IO)
		 || (fc == XPT_SMP_IO) || (fc == XPT_DEV_MATCH)
		 || (fc == XPT_DEV_ADVINFO)
		 || (fc == XPT_NVME_ADMIN) || (fc == XPT_NVME_IO)) {
			error = passmemsetup(periph, io_req);
			if (error != 0)
				goto camioqueue_error;
		} else
			io_req->mapinfo.num_bufs_used = 0;

		cam_periph_lock(periph);

		/*
		 * Everything goes on the incoming queue initially.
		 */
		TAILQ_INSERT_TAIL(&softc->incoming_queue, io_req, links);

		/*
		 * If the CCB is queued, and is not a user CCB, then
		 * we need to allocate a slot for it.  Call xpt_schedule()
		 * so that our start routine will get called when a CCB is
		 * available.
		 */
		if ((fc & XPT_FC_QUEUED)
		 && ((fc & XPT_FC_USER_CCB) == 0)) {
			xpt_schedule(periph, priority);
			break;
		} 

		/*
		 * At this point, the CCB in question is either an
		 * immediate CCB (like XPT_DEV_ADVINFO) or it is a user CCB
		 * and therefore should be malloced, not allocated via a slot.
		 * Remove the CCB from the incoming queue and add it to the
		 * active queue.
		 */
		TAILQ_REMOVE(&softc->incoming_queue, io_req, links);
		TAILQ_INSERT_TAIL(&softc->active_queue, io_req, links);

		xpt_action(ccb);

		/*
		 * If this is not a queued CCB (i.e. it is an immediate CCB),
		 * then it is already done.  We need to put it on the done
		 * queue for the user to fetch.
		 */
		if ((fc & XPT_FC_QUEUED) == 0) {
			TAILQ_REMOVE(&softc->active_queue, io_req, links);
			TAILQ_INSERT_TAIL(&softc->done_queue, io_req, links);
		}
		break;

camioqueue_error:
		uma_zfree(softc->pass_zone, io_req);
		cam_periph_lock(periph);
		break;
	}
	case CAMIOGET:
	{
		union ccb **user_ccb;
		struct pass_io_req *io_req;
		int old_error;

#ifdef COMPAT_FREEBSD32
		if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
			error = ENOTTY;
			goto bailout;
		}
#endif
		user_ccb = (union ccb **)addr;
		old_error = 0;

		io_req = TAILQ_FIRST(&softc->done_queue);
		if (io_req == NULL) {
			error = ENOENT;
			break;
		}

		/*
		 * Remove the I/O from the done queue.
		 */
		TAILQ_REMOVE(&softc->done_queue, io_req, links);

		/*
		 * We have to drop the lock during the copyout because the
		 * copyout can result in VM faults that require sleeping.
		 */
		cam_periph_unlock(periph);

		/*
		 * Do any needed copies (e.g. for reads) and revert the
		 * pointers in the CCB back to the user's pointers.
		 */
		error = passmemdone(periph, io_req);

		old_error = error;

		io_req->ccb.ccb_h.periph_links = io_req->user_periph_links;
		io_req->ccb.ccb_h.periph_priv = io_req->user_periph_priv;

#if 0
		xpt_print(periph->path, "Copying to user CCB %p from "
			  "kernel address %p\n", *user_ccb, &io_req->ccb);
#endif

		error = copyout(&io_req->ccb, *user_ccb, sizeof(union ccb));
		if (error != 0) {
			xpt_print(periph->path, "Copy to user CCB %p from "
				  "kernel address %p failed with error %d\n",
				  *user_ccb, &io_req->ccb, error);
		}

		/*
		 * Prefer the first error we got back, and make sure we
		 * don't overwrite bad status with good.
		 */
		if (old_error != 0)
			error = old_error;

		cam_periph_lock(periph);

		/*
		 * At this point, if there was an error, we could potentially
		 * re-queue the I/O and try again.  But why?  The error
		 * would almost certainly happen again.  We might as well
		 * not leak memory.
		 */
		uma_zfree(softc->pass_zone, io_req);
		break;
	}
	default:
		error = cam_periph_ioctl(periph, cmd, addr, passerror);
		break;
	}

bailout:
	cam_periph_unlock(periph);

	return(error);
}