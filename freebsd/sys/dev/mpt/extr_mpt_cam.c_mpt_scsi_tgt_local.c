#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {size_t DataLength; int /*<<< orphan*/  Address; int /*<<< orphan*/  TargetAssistFlags; int /*<<< orphan*/ * SGL; scalar_t__ RelativeOffset; int /*<<< orphan*/  LUN; void* ReplyWord; void* MsgContext; int /*<<< orphan*/  Function; int /*<<< orphan*/  Tag; int /*<<< orphan*/  QueueTag; int /*<<< orphan*/  InitiatorTag; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int uint32_t ;
struct mpt_softc {int scsi_tgt_handler_id; scalar_t__ is_spi; scalar_t__ is_sas; } ;
struct TYPE_21__ {int index; int /*<<< orphan*/  req_pbuf; TYPE_1__* req_vbuf; } ;
typedef  TYPE_2__ request_t ;
struct TYPE_22__ {scalar_t__ resid; int is_local; int reply_desc; size_t bytes_xfered; int /*<<< orphan*/  state; TYPE_2__* req; int /*<<< orphan*/ * ccb; } ;
typedef  TYPE_3__ mpt_tgt_state_t ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  TYPE_1__ SGE_SIMPLE32 ;
typedef  TYPE_1__* PTR_MSG_TARGET_ASSIST_REQUEST ;
typedef  TYPE_1__* PTR_MPI_TARGET_SSP_CMD_BUFFER ;
typedef  TYPE_1__* PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_EXTLUN_BYTE_SWIZZLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_FUNCTION_TARGET_ASSIST ; 
 int MPI_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI_SGE_FLAGS_END_OF_LIST ; 
 int MPI_SGE_FLAGS_HOST_TO_IOC ; 
 int MPI_SGE_FLAGS_LAST_ELEMENT ; 
 int MPI_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  MPI_pSGE_SET_FLAGS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MPI_pSGE_SET_LENGTH (TYPE_1__*,size_t) ; 
 int MPT_RQSL (struct mpt_softc*) ; 
 TYPE_3__* MPT_TGT_STATE (struct mpt_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  TARGET_ASSIST_FLAGS_DATA_DIRECTION ; 
 int /*<<< orphan*/  TGT_STATE_MOVING_DATA ; 
 int /*<<< orphan*/  TGT_STATE_MOVING_DATA_AND_STATUS ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (size_t,int) ; 
 TYPE_2__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_scsi_tgt_status (struct mpt_softc*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_2__*) ; 

__attribute__((used)) static void
mpt_scsi_tgt_local(struct mpt_softc *mpt, request_t *cmd_req,
    lun_id_t lun, int send, uint8_t *data, size_t length)
{
	mpt_tgt_state_t *tgt;
	PTR_MSG_TARGET_ASSIST_REQUEST ta;
	SGE_SIMPLE32 *se;
	uint32_t flags;
	uint8_t *dptr;
	bus_addr_t pptr;
	request_t *req;

	/*
	 * We enter with resid set to the data load for the command.
	 */
	tgt = MPT_TGT_STATE(mpt, cmd_req);
	if (length == 0 || tgt->resid == 0) {
		tgt->resid = 0;
		mpt_scsi_tgt_status(mpt, NULL, cmd_req, 0, NULL, 0);
		return;
	}

	if ((req = mpt_get_request(mpt, FALSE)) == NULL) {
		mpt_prt(mpt, "out of resources- dropping local response\n");
		return;
	}
	tgt->is_local = 1;


	memset(req->req_vbuf, 0, MPT_RQSL(mpt));
	ta = req->req_vbuf;

	if (mpt->is_sas) {
		PTR_MPI_TARGET_SSP_CMD_BUFFER ssp = cmd_req->req_vbuf;
		ta->QueueTag = ssp->InitiatorTag;
	} else if (mpt->is_spi) {
		PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER sp = cmd_req->req_vbuf;
		ta->QueueTag = sp->Tag;
	}
	ta->Function = MPI_FUNCTION_TARGET_ASSIST;
	ta->MsgContext = htole32(req->index | mpt->scsi_tgt_handler_id);
	ta->ReplyWord = htole32(tgt->reply_desc);
	be64enc(ta->LUN, CAM_EXTLUN_BYTE_SWIZZLE(lun));
	ta->RelativeOffset = 0;
	ta->DataLength = length;

	dptr = req->req_vbuf;
	dptr += MPT_RQSL(mpt);
	pptr = req->req_pbuf;
	pptr += MPT_RQSL(mpt);
	memcpy(dptr, data, min(length, MPT_RQSL(mpt)));

	se = (SGE_SIMPLE32 *) &ta->SGL[0];
	memset(se, 0,sizeof (*se));

	flags = MPI_SGE_FLAGS_SIMPLE_ELEMENT;
	if (send) {
		ta->TargetAssistFlags |= TARGET_ASSIST_FLAGS_DATA_DIRECTION;
		flags |= MPI_SGE_FLAGS_HOST_TO_IOC;
	}
	se->Address = pptr;
	MPI_pSGE_SET_LENGTH(se, length);
	flags |= MPI_SGE_FLAGS_LAST_ELEMENT;
	flags |= MPI_SGE_FLAGS_END_OF_LIST | MPI_SGE_FLAGS_END_OF_BUFFER;
	MPI_pSGE_SET_FLAGS(se, flags);

	tgt->ccb = NULL;
	tgt->req = req;
	tgt->resid -= length;
	tgt->bytes_xfered = length;
#ifdef	WE_TRUST_AUTO_GOOD_STATUS
	tgt->state = TGT_STATE_MOVING_DATA_AND_STATUS;
#else
	tgt->state = TGT_STATE_MOVING_DATA;
#endif
	mpt_send_cmd(mpt, req);
}