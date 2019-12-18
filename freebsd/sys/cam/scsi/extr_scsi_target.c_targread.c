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
typedef  int /*<<< orphan*/  user_ccb ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct uio {int uio_resid; } ;
struct descr_queue {int dummy; } ;
struct targ_softc {int /*<<< orphan*/  periph; int /*<<< orphan*/  path; struct descr_queue abort_queue; struct descr_queue user_ccb_queue; } ;
struct targ_cmd_descr {union ccb* user_ccb; scalar_t__ targ_descr; } ;
struct cdev {int dummy; } ;
typedef  struct descr_queue ccb_queue ;
struct ccb_hdr {union ccb* user_ccb; scalar_t__ targ_descr; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int EAGAIN ; 
 int ENOSPC ; 
 int ERESTART ; 
 int IO_NDELAY ; 
 int PCATCH ; 
 int PRIBIO ; 
 struct targ_cmd_descr* TAILQ_FIRST (struct descr_queue*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct descr_queue*,struct targ_cmd_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (int /*<<< orphan*/ ) ; 
 int cam_periph_sleep (int /*<<< orphan*/ ,struct descr_queue*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 TYPE_2__ periph_links ; 
 int /*<<< orphan*/  suword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int targreturnccb (struct targ_softc*,union ccb*) ; 
 int /*<<< orphan*/  tqe ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
targread(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct descr_queue	*abort_queue;
	struct targ_cmd_descr	*user_descr;
	struct targ_softc	*softc;
	struct ccb_queue  *user_queue;
	struct ccb_hdr	  *ccb_h;
	union  ccb	  *user_ccb;
	int		   read_len, error;

	error = 0;
	read_len = 0;
	devfs_get_cdevpriv((void **)&softc);
	user_queue = &softc->user_ccb_queue;
	abort_queue = &softc->abort_queue;
	CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH, ("targread\n"));

	/* If no data is available, wait or return immediately */
	cam_periph_lock(softc->periph);
	ccb_h = TAILQ_FIRST(user_queue);
	user_descr = TAILQ_FIRST(abort_queue);
	while (ccb_h == NULL && user_descr == NULL) {
		if ((ioflag & IO_NDELAY) == 0) {
			error = cam_periph_sleep(softc->periph, user_queue,
			    PRIBIO | PCATCH, "targrd", 0);
			ccb_h = TAILQ_FIRST(user_queue);
			user_descr = TAILQ_FIRST(abort_queue);
			if (error != 0) {
				if (error == ERESTART) {
					continue;
				} else {
					goto read_fail;
				}
			}
		} else {
			cam_periph_unlock(softc->periph);
			return (EAGAIN);
		}
	}

	/* Data is available so fill the user's buffer */
	while (ccb_h != NULL) {
		struct targ_cmd_descr *descr;

		if (uio->uio_resid < sizeof(user_ccb))
			break;
		TAILQ_REMOVE(user_queue, ccb_h, periph_links.tqe);
		descr = (struct targ_cmd_descr *)ccb_h->targ_descr;
		user_ccb = descr->user_ccb;
		CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH,
			  ("targread ccb %p (%p)\n", ccb_h, user_ccb));
		error = targreturnccb(softc, (union ccb *)ccb_h);
		if (error != 0)
			goto read_fail;
		cam_periph_unlock(softc->periph);
		error = uiomove((caddr_t)&user_ccb, sizeof(user_ccb), uio);
		cam_periph_lock(softc->periph);
		if (error != 0)
			goto read_fail;
		read_len += sizeof(user_ccb);

		ccb_h = TAILQ_FIRST(user_queue);
	}

	/* Flush out any aborted descriptors */
	while (user_descr != NULL) {
		if (uio->uio_resid < sizeof(user_ccb))
			break;
		TAILQ_REMOVE(abort_queue, user_descr, tqe);
		user_ccb = user_descr->user_ccb;
		CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH,
			  ("targread aborted descr %p (%p)\n",
			  user_descr, user_ccb));
		suword(&user_ccb->ccb_h.status, CAM_REQ_ABORTED);
		cam_periph_unlock(softc->periph);
		error = uiomove((caddr_t)&user_ccb, sizeof(user_ccb), uio);
		cam_periph_lock(softc->periph);
		if (error != 0)
			goto read_fail;
		read_len += sizeof(user_ccb);

		user_descr = TAILQ_FIRST(abort_queue);
	}

	/*
	 * If we've successfully read some amount of data, don't report an
	 * error.  If the error is persistent, it will be reported on the
	 * next read().
	 */
	if (read_len == 0 && uio->uio_resid != 0)
		error = ENOSPC;

read_fail:
	cam_periph_unlock(softc->periph);
	return (error);
}