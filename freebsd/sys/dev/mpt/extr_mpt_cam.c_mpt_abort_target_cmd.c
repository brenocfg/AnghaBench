#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int scsi_tgt_handler_id; scalar_t__ is_sas; scalar_t__ is_fc; } ;
struct TYPE_10__ {int index; TYPE_2__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_12__ {int reply_desc; } ;
struct TYPE_11__ {void* ReplyWord; int /*<<< orphan*/  Function; int /*<<< orphan*/  AbortType; void* MsgContext; } ;
typedef  TYPE_2__* PTR_MSG_TARGET_MODE_ABORT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_FUNCTION_TARGET_MODE_ABORT ; 
 TYPE_8__* MPT_TGT_STATE (struct mpt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  TARGET_MODE_ABORT_TYPE_EXACT_IO ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_send_handshake_cmd (struct mpt_softc*,int,TYPE_1__*) ; 

__attribute__((used)) static int
mpt_abort_target_cmd(struct mpt_softc *mpt, request_t *cmd_req)
{
	int error;
	request_t *req;
	PTR_MSG_TARGET_MODE_ABORT abtp;

	req = mpt_get_request(mpt, FALSE);
	if (req == NULL) {
		return (-1);
	}
	abtp = req->req_vbuf;
	memset(abtp, 0, sizeof (*abtp));

	abtp->MsgContext = htole32(req->index | mpt->scsi_tgt_handler_id);
	abtp->AbortType = TARGET_MODE_ABORT_TYPE_EXACT_IO;
	abtp->Function = MPI_FUNCTION_TARGET_MODE_ABORT;
	abtp->ReplyWord = htole32(MPT_TGT_STATE(mpt, cmd_req)->reply_desc);
	error = 0;
	if (mpt->is_fc || mpt->is_sas) {
		mpt_send_cmd(mpt, req);
	} else {
		error = mpt_send_handshake_cmd(mpt, sizeof(*req), req);
	}
	return (error);
}