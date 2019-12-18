#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  U32 ;
typedef  void* U16 ;
struct TYPE_7__ {int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_6__ {int /*<<< orphan*/  SlotStatus; void* Slot; void* EnclosureHandle; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Action; int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ MPI2_SEP_REQUEST ;
typedef  TYPE_2__ MPI2_SEP_REPLY ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR ; 
 int /*<<< orphan*/  MPI2_SEP_REQ_ACTION_WRITE_STATUS ; 
 int /*<<< orphan*/  MPI2_SEP_REQ_FLAGS_ENCLOSURE_SLOT_ADDRESS ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int errno ; 
 scalar_t__ mps_pass_command (int,TYPE_1__*,int,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
mps_set_slot_status(int fd, U16 handle, U16 slot, U32 status)
{
	MPI2_SEP_REQUEST req;
	MPI2_SEP_REPLY reply;

	bzero(&req, sizeof(req));
	req.Function = MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR;
	req.Action = MPI2_SEP_REQ_ACTION_WRITE_STATUS;
	req.Flags = MPI2_SEP_REQ_FLAGS_ENCLOSURE_SLOT_ADDRESS;
	req.EnclosureHandle = handle;
	req.Slot = slot;
	req.SlotStatus = status;

	if (mps_pass_command(fd, &req, sizeof(req), &reply, sizeof(reply),
	    NULL, 0, NULL, 0, 30) != 0)
		return (errno);

	if (!IOC_STATUS_SUCCESS(reply.IOCStatus))
		return (EIO);
	return (0);
}