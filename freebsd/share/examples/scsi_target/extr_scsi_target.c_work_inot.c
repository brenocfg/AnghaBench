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
typedef  union ccb {int dummy; } ccb ;
struct TYPE_4__ {int status; } ;
struct ccb_immediate_notify {int arg; TYPE_2__ ccb_h; } ;
typedef  int cam_status ;
struct TYPE_3__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
#define  CAM_BDR_SENT 140 
#define  CAM_MESSAGE_RECV 139 
#define  CAM_REQ_ABORTED 138 
#define  CAM_SCSI_BUS_RESET 137 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
#define  MSG_ABORT_TASK 136 
#define  MSG_ABORT_TASK_SET 135 
#define  MSG_CLEAR_TASK_SET 134 
#define  MSG_INITIATOR_DET_ERR 133 
#define  MSG_MESSAGE_REJECT 132 
#define  MSG_NOOP 131 
#define  MSG_PARITY_ERROR 130 
#define  MSG_TARGET_RESET 129 
#define  MSG_TASK_COMPLETE 128 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UA_BDR ; 
 int /*<<< orphan*/  UA_BUS_RESET ; 
 int /*<<< orphan*/  abort_all_pending () ; 
 scalar_t__ debug ; 
 TYPE_1__ periph_links ; 
 int /*<<< orphan*/  send_ccb (union ccb*,int) ; 
 int /*<<< orphan*/  tcmd_ua (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  work_queue ; 

__attribute__((used)) static int
work_inot(struct ccb_immediate_notify *inot)
{
	cam_status status;

	if (debug)
		warnx("Working on INOT %p", inot);

	status = inot->ccb_h.status;
	status &= CAM_STATUS_MASK;

	switch (status) {
	case CAM_SCSI_BUS_RESET:
		tcmd_ua(CAM_TARGET_WILDCARD, UA_BUS_RESET);
		abort_all_pending();
		break;
	case CAM_BDR_SENT:
		tcmd_ua(CAM_TARGET_WILDCARD, UA_BDR);
		abort_all_pending();
		break;
	case CAM_MESSAGE_RECV:
		switch (inot->arg) {
		case MSG_TASK_COMPLETE:
		case MSG_INITIATOR_DET_ERR:
		case MSG_ABORT_TASK_SET:
		case MSG_MESSAGE_REJECT:
		case MSG_NOOP:
		case MSG_PARITY_ERROR:
		case MSG_TARGET_RESET:
		case MSG_ABORT_TASK:
		case MSG_CLEAR_TASK_SET:
		default:
			warnx("INOT message %#x", inot->arg);
			break;
		}
		break;
	case CAM_REQ_ABORTED:
		warnx("INOT %p aborted", inot);
		break;
	default:
		warnx("Unhandled INOT status %#x", status);
		break;
	}

	/* Requeue on SIM */
	TAILQ_REMOVE(&work_queue, &inot->ccb_h, periph_links.tqe);
	send_ccb((union ccb *)inot, /*priority*/1);

	return (1);
}