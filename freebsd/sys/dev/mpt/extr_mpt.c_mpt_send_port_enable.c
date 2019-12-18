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
struct mpt_softc {scalar_t__ is_fc; scalar_t__ is_sas; } ;
struct TYPE_8__ {int index; TYPE_2__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int PortNumber; int /*<<< orphan*/  MsgContext; int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ MSG_PORT_ENABLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_FUNCTION_PORT_ENABLE ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int MPT_REPLY_HANDLER_CONFIG ; 
 int /*<<< orphan*/  MPT_RQSL (struct mpt_softc*) ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_check_doorbell (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,int) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_send_port_enable(struct mpt_softc *mpt, int port)
{
	request_t	*req;
	MSG_PORT_ENABLE *enable_req;
	int		 error;

	req = mpt_get_request(mpt, /*sleep_ok*/FALSE);
	if (req == NULL)
		return (-1);

	enable_req = req->req_vbuf;
	memset(enable_req, 0,  MPT_RQSL(mpt));

	enable_req->Function   = MPI_FUNCTION_PORT_ENABLE;
	enable_req->MsgContext = htole32(req->index | MPT_REPLY_HANDLER_CONFIG);
	enable_req->PortNumber = port;

	mpt_check_doorbell(mpt);
	mpt_lprt(mpt, MPT_PRT_DEBUG, "enabling port %d\n", port);

	mpt_send_cmd(mpt, req);
	error = mpt_wait_req(mpt, req, REQ_STATE_DONE, REQ_STATE_DONE,
	    FALSE, (mpt->is_sas || mpt->is_fc)? 300000 : 30000);
	if (error != 0) {
		mpt_prt(mpt, "port %d enable timed out\n", port);
		return (-1);
	}
	mpt_free_request(mpt, req);
	mpt_lprt(mpt, MPT_PRT_DEBUG, "enabled port %d\n", port);
	return (0);
}