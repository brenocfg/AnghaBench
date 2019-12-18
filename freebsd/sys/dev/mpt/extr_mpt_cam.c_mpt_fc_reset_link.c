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
struct mpt_softc {int dummy; } ;
struct TYPE_8__ {int index; TYPE_2__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int /*<<< orphan*/  MsgContext; int /*<<< orphan*/  Function; int /*<<< orphan*/  SendFlags; } ;
typedef  TYPE_2__* PTR_MSG_FC_PRIMITIVE_SEND_REQUEST ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_FC_PRIM_SEND_FLAGS_RESET_LINK ; 
 int /*<<< orphan*/  MPI_FUNCTION_FC_PRIMITIVE_SEND ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int fc_els_handler_id ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_fc_reset_link(struct mpt_softc *mpt, int dowait)
{
	int r = 0;
	request_t *req;
	PTR_MSG_FC_PRIMITIVE_SEND_REQUEST fc;

 	req = mpt_get_request(mpt, FALSE);
	if (req == NULL) {
		return (ENOMEM);
	}
	fc = req->req_vbuf;
	memset(fc, 0, sizeof(*fc));
	fc->SendFlags = MPI_FC_PRIM_SEND_FLAGS_RESET_LINK;
	fc->Function = MPI_FUNCTION_FC_PRIMITIVE_SEND;
	fc->MsgContext = htole32(req->index | fc_els_handler_id);
	mpt_send_cmd(mpt, req);
	if (dowait) {
		r = mpt_wait_req(mpt, req, REQ_STATE_DONE,
		    REQ_STATE_DONE, FALSE, 60 * 1000);
		if (r == 0) {
			mpt_free_request(mpt, req);
		}
	}
	return (r);
}