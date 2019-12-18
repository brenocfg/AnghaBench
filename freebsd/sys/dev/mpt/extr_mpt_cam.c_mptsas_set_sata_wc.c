#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mptsas_devinfo {int /*<<< orphan*/  bus; int /*<<< orphan*/  target_id; } ;
struct mpt_softc {int dummy; } ;
struct TYPE_8__ {int index; int /*<<< orphan*/  IOCStatus; TYPE_2__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int* CommandFIS; int /*<<< orphan*/  MsgContext; scalar_t__ DataLength; int /*<<< orphan*/  ConnectionRate; scalar_t__ PassthroughFlags; int /*<<< orphan*/  Bus; int /*<<< orphan*/  TargetID; int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ SataPassthroughRequest_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_FUNCTION_SATA_PASSTHROUGH ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI_SATA_PT_REQ_CONNECT_RATE_NEGOTIATED ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_check_doorbell (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sata_pass_handler_id ; 

__attribute__((used)) static void
mptsas_set_sata_wc(struct mpt_softc *mpt, struct mptsas_devinfo *devinfo,
	int enabled)
{
	SataPassthroughRequest_t	*pass;
	request_t *req;
	int error, status;

	req = mpt_get_request(mpt, 0);
	if (req == NULL)
		return;

	pass = req->req_vbuf;
	bzero(pass, sizeof(SataPassthroughRequest_t));
	pass->Function = MPI_FUNCTION_SATA_PASSTHROUGH;
	pass->TargetID = devinfo->target_id;
	pass->Bus = devinfo->bus;
	pass->PassthroughFlags = 0;
	pass->ConnectionRate = MPI_SATA_PT_REQ_CONNECT_RATE_NEGOTIATED;
	pass->DataLength = 0;
	pass->MsgContext = htole32(req->index | sata_pass_handler_id);
	pass->CommandFIS[0] = 0x27;
	pass->CommandFIS[1] = 0x80;
	pass->CommandFIS[2] = 0xef;
	pass->CommandFIS[3] = (enabled) ? 0x02 : 0x82;
	pass->CommandFIS[7] = 0x40;
	pass->CommandFIS[15] = 0x08;

	mpt_check_doorbell(mpt);
	mpt_send_cmd(mpt, req);
	error = mpt_wait_req(mpt, req, REQ_STATE_DONE, REQ_STATE_DONE, 0,
			     10 * 1000);
	if (error) {
		mpt_free_request(mpt, req);
		printf("error %d sending passthrough\n", error);
		return;
	}

	status = le16toh(req->IOCStatus);
	if (status != MPI_IOCSTATUS_SUCCESS) {
		mpt_free_request(mpt, req);
		printf("IOCSTATUS %d\n", status);
		return;
	}

	mpt_free_request(mpt, req);
}