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
struct iscsi_session {int dummy; } ;
struct iscsi_outstanding {TYPE_2__* io_ccb; } ;
typedef  int cam_status ;
struct TYPE_3__ {int status; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int CAM_SIM_QUEUED ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsi_outstanding_remove (struct iscsi_session*,struct iscsi_outstanding*) ; 
 int /*<<< orphan*/  xpt_done (TYPE_2__*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iscsi_session_terminate_task(struct iscsi_session *is,
    struct iscsi_outstanding *io, cam_status status)
{

	ISCSI_SESSION_LOCK_ASSERT(is);

	if (io->io_ccb != NULL) {
		io->io_ccb->ccb_h.status &= ~(CAM_SIM_QUEUED | CAM_STATUS_MASK);
		io->io_ccb->ccb_h.status |= status;
		if ((io->io_ccb->ccb_h.status & CAM_DEV_QFRZN) == 0) {
			io->io_ccb->ccb_h.status |= CAM_DEV_QFRZN;
			xpt_freeze_devq(io->io_ccb->ccb_h.path, 1);
			ISCSI_SESSION_DEBUG(is, "freezing devq");
		}
		xpt_done(io->io_ccb);
	}
	iscsi_outstanding_remove(is, io);
}