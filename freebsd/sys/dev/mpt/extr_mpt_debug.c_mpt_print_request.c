#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Function; } ;
typedef  int /*<<< orphan*/  PTR_MSG_TARGET_ASSIST_REQUEST ;
typedef  int /*<<< orphan*/  MSG_TARGET_STATUS_SEND_REQUEST ;
typedef  int /*<<< orphan*/  MSG_SCSI_TASK_MGMT ;
typedef  int /*<<< orphan*/  MSG_SCSI_IO_REQUEST ;
typedef  TYPE_1__ MSG_REQUEST_HEADER ;

/* Variables and functions */
#define  MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH 132 
#define  MPI_FUNCTION_SCSI_IO_REQUEST 131 
#define  MPI_FUNCTION_SCSI_TASK_MGMT 130 
#define  MPI_FUNCTION_TARGET_ASSIST 129 
#define  MPI_FUNCTION_TARGET_STATUS_SEND 128 
 int /*<<< orphan*/  mpt_print_request_hdr (TYPE_1__*) ; 
 int /*<<< orphan*/  mpt_print_scsi_io_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_print_scsi_target_assist_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_print_scsi_target_status_send_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_print_scsi_tmf_request (int /*<<< orphan*/ *) ; 

void
mpt_print_request(void *vreq)
{
	MSG_REQUEST_HEADER *req = vreq;

	switch (req->Function) {
	case MPI_FUNCTION_SCSI_IO_REQUEST:
	case MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
		mpt_print_scsi_io_request((MSG_SCSI_IO_REQUEST *)req);
		break;
	case MPI_FUNCTION_SCSI_TASK_MGMT:
		mpt_print_scsi_tmf_request((MSG_SCSI_TASK_MGMT *)req);
		break;
	case MPI_FUNCTION_TARGET_ASSIST:
		mpt_print_scsi_target_assist_request(
		    (PTR_MSG_TARGET_ASSIST_REQUEST)req);
		break;
	case MPI_FUNCTION_TARGET_STATUS_SEND:
		mpt_print_scsi_target_status_send_request(
		    (MSG_TARGET_STATUS_SEND_REQUEST *)req);
		break;
	default:
		mpt_print_request_hdr(req);
		break;
	}
}