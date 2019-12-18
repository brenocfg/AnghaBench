#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int /*<<< orphan*/  request_pending_list; } ;
struct TYPE_10__ {int state; int /*<<< orphan*/  IOCStatus; scalar_t__ req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_13__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  Header; } ;
struct TYPE_12__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  Header; } ;
struct TYPE_11__ {int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_2__ MSG_DEFAULT_REPLY ;
typedef  TYPE_3__ MSG_CONFIG_REPLY ;
typedef  TYPE_4__ MSG_CONFIG ;

/* Variables and functions */
 int REQ_STATE_DONE ; 
 int REQ_STATE_NEED_WAKEUP ; 
 int REQ_STATE_QUEUED ; 
 int REQ_STATE_TIMEDOUT ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static int
mpt_config_reply_handler(struct mpt_softc *mpt, request_t *req,
 uint32_t reply_desc, MSG_DEFAULT_REPLY *reply_frame)
{

	if (req != NULL) {
		if (reply_frame != NULL) {
			MSG_CONFIG *cfgp;
			MSG_CONFIG_REPLY *reply;

			cfgp = (MSG_CONFIG *)req->req_vbuf;
			reply = (MSG_CONFIG_REPLY *)reply_frame;
			req->IOCStatus = le16toh(reply_frame->IOCStatus);
			bcopy(&reply->Header, &cfgp->Header,
			      sizeof(cfgp->Header));
			cfgp->ExtPageLength = reply->ExtPageLength;
			cfgp->ExtPageType = reply->ExtPageType;
		}
		req->state &= ~REQ_STATE_QUEUED;
		req->state |= REQ_STATE_DONE;
		TAILQ_REMOVE(&mpt->request_pending_list, req, links);
		if ((req->state & REQ_STATE_NEED_WAKEUP) != 0) {
			wakeup(req);
		} else if ((req->state & REQ_STATE_TIMEDOUT) != 0) {
			/*
			 * Whew- we can free this request (late completion)
			 */
			mpt_free_request(mpt, req);
		}
	}

	return (TRUE);
}