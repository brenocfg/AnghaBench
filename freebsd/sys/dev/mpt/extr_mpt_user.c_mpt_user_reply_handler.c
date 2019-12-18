#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_user_raid_action_result {int /*<<< orphan*/  action_data; int /*<<< orphan*/  volume_status; int /*<<< orphan*/  action_status; } ;
struct mpt_softc {int /*<<< orphan*/  request_pending_list; } ;
struct TYPE_7__ {int state; scalar_t__ req_vbuf; int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_8__ {int /*<<< orphan*/  ActionData; int /*<<< orphan*/  VolumeStatus; int /*<<< orphan*/  ActionStatus; int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_2__ MSG_RAID_ACTION_REPLY ;
typedef  int /*<<< orphan*/  MSG_DEFAULT_REPLY ;

/* Variables and functions */
 int MPT_RQSL (struct mpt_softc*) ; 
 int REQ_STATE_DONE ; 
 int REQ_STATE_NEED_WAKEUP ; 
 int REQ_STATE_QUEUED ; 
 int REQ_STATE_TIMEDOUT ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static int
mpt_user_reply_handler(struct mpt_softc *mpt, request_t *req,
    uint32_t reply_desc, MSG_DEFAULT_REPLY *reply_frame)
{
	MSG_RAID_ACTION_REPLY *reply;
	struct mpt_user_raid_action_result *res;

	if (req == NULL)
		return (TRUE);

	if (reply_frame != NULL) {
		reply = (MSG_RAID_ACTION_REPLY *)reply_frame;
		req->IOCStatus = le16toh(reply->IOCStatus);
		res = (struct mpt_user_raid_action_result *)
		    (((uint8_t *)req->req_vbuf) + MPT_RQSL(mpt));
		res->action_status = reply->ActionStatus;
		res->volume_status = reply->VolumeStatus;
		bcopy(&reply->ActionData, res->action_data,
		    sizeof(res->action_data));
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

	return (TRUE);
}