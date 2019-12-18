#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int /*<<< orphan*/  request_pending_list; } ;
struct TYPE_7__ {int state; int /*<<< orphan*/ * ccb; } ;
typedef  TYPE_1__ request_t ;
typedef  int /*<<< orphan*/  MSG_DEFAULT_REPLY ;

/* Variables and functions */
 int REQ_STATE_DONE ; 
 int REQ_STATE_NEED_WAKEUP ; 
 int REQ_STATE_QUEUED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_raid_reply_frame_handler (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static int
mpt_raid_reply_handler(struct mpt_softc *mpt, request_t *req,
    uint32_t reply_desc, MSG_DEFAULT_REPLY *reply_frame)
{
	int free_req;

	if (req == NULL)
		return (TRUE);

	free_req = TRUE;
	if (reply_frame != NULL)
		free_req = mpt_raid_reply_frame_handler(mpt, req, reply_frame);
#ifdef NOTYET
	else if (req->ccb != NULL) {
		/* Complete Quiesce CCB with error... */
	}
#endif

	req->state &= ~REQ_STATE_QUEUED;
	req->state |= REQ_STATE_DONE;
	TAILQ_REMOVE(&mpt->request_pending_list, req, links);

	if ((req->state & REQ_STATE_NEED_WAKEUP) != 0) {
		wakeup(req);
	} else if (free_req) {
		mpt_free_request(mpt, req);
	}

	return (TRUE);
}