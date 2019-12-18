#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mpt_softc {int dummy; } ;
struct TYPE_9__ {int req_pbuf; int index; int state; int /*<<< orphan*/  serno; TYPE_4__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
typedef  int bus_addr_t ;
struct TYPE_12__ {int BufferCount; int /*<<< orphan*/  SGL; void* MsgContext; int /*<<< orphan*/  Function; } ;
struct TYPE_11__ {void* Address; void* FlagsLength; } ;
struct TYPE_10__ {int ContextSize; int /*<<< orphan*/ * TransactionDetails; void** TransactionContext; scalar_t__ Flags; } ;
typedef  TYPE_2__* PTR_SGE_TRANSACTION32 ;
typedef  TYPE_3__* PTR_SGE_SIMPLE32 ;
typedef  TYPE_4__ MSG_LINK_SERVICE_BUFFER_POST_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPI_FUNCTION_FC_LINK_SRVC_BUF_POST ; 
 int MPI_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI_SGE_FLAGS_END_OF_LIST ; 
 int MPI_SGE_FLAGS_HOST_TO_IOC ; 
 int MPI_SGE_FLAGS_LAST_ELEMENT ; 
 int MPI_SGE_FLAGS_SHIFT ; 
 int MPI_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int MPT_NRFM (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  MPT_REQUEST_AREA ; 
 int MPT_RQSL (struct mpt_softc*) ; 
 int REQ_STATE_LOCKED ; 
 int fc_els_handler_id ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 

__attribute__((used)) static void
mpt_fc_post_els(struct mpt_softc *mpt, request_t *req, int ioindex)
{
	MSG_LINK_SERVICE_BUFFER_POST_REQUEST *fc;
	PTR_SGE_TRANSACTION32 tep;
	PTR_SGE_SIMPLE32 se;
	bus_addr_t paddr;
	uint32_t fl;

	paddr = req->req_pbuf;
	paddr += MPT_RQSL(mpt);

	fc = req->req_vbuf;
	memset(fc, 0, MPT_REQUEST_AREA);
	fc->BufferCount = 1;
	fc->Function = MPI_FUNCTION_FC_LINK_SRVC_BUF_POST;
	fc->MsgContext = htole32(req->index | fc_els_handler_id);

	/*
	 * Okay, set up ELS buffer pointers. ELS buffer pointers
	 * consist of a TE SGL element (with details length of zero)
	 * followed by a SIMPLE SGL element which holds the address
	 * of the buffer.
	 */

	tep = (PTR_SGE_TRANSACTION32) &fc->SGL;

	tep->ContextSize = 4;
	tep->Flags = 0;
	tep->TransactionContext[0] = htole32(ioindex);

	se = (PTR_SGE_SIMPLE32) &tep->TransactionDetails[0];
	fl =
		MPI_SGE_FLAGS_HOST_TO_IOC	|
		MPI_SGE_FLAGS_SIMPLE_ELEMENT	|
		MPI_SGE_FLAGS_LAST_ELEMENT	|
		MPI_SGE_FLAGS_END_OF_LIST	|
		MPI_SGE_FLAGS_END_OF_BUFFER;
	fl <<= MPI_SGE_FLAGS_SHIFT;
	fl |= (MPT_NRFM(mpt) - MPT_RQSL(mpt));
	se->FlagsLength = htole32(fl);
	se->Address = htole32((uint32_t) paddr);
	mpt_lprt(mpt, MPT_PRT_DEBUG,
	    "add ELS index %d ioindex %d for %p:%u\n",
	    req->index, ioindex, req, req->serno);
	KASSERT(((req->state & REQ_STATE_LOCKED) != 0),
	    ("mpt_fc_post_els: request not locked"));
	mpt_send_cmd(mpt, req);
}