#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct mpt_softc {scalar_t__ reset_cnt; } ;
typedef  int sbintime_t ;
struct TYPE_5__ {int state; TYPE_2__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
typedef  int mpt_req_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ MSG_REQUEST_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PUSER ; 
 int REQ_STATE_NEED_WAKEUP ; 
 int REQ_STATE_TIMEDOUT ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  mpt_intr (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mpt_sleep (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

int
mpt_wait_req(struct mpt_softc *mpt, request_t *req,
	     mpt_req_state_t state, mpt_req_state_t mask,
	     int sleep_ok, int time_ms)
{
	int   timeout;
	u_int saved_cnt;
	sbintime_t sbt;

	/*
	 * time_ms is in ms, 0 indicates infinite wait.
	 * Convert to sbintime_t or 500us units depending on
	 * our sleep mode.
	 */
	if (sleep_ok != 0) {
		sbt = SBT_1MS * time_ms;
		/* Set timeout as well so final timeout check works. */
		timeout = time_ms;
	} else {
		sbt = 0; /* Squelch bogus gcc warning. */
		timeout = time_ms * 2;
	}
	req->state |= REQ_STATE_NEED_WAKEUP;
	mask &= ~REQ_STATE_NEED_WAKEUP;
	saved_cnt = mpt->reset_cnt;
	while ((req->state & mask) != state && mpt->reset_cnt == saved_cnt) {
		if (sleep_ok != 0) {
			if (mpt_sleep(mpt, req, PUSER, "mptreq", sbt) ==
			    EWOULDBLOCK) {
				timeout = 0;
				break;
			}
		} else {
			if (time_ms != 0 && --timeout == 0) {
				break;
			}
			DELAY(500);
			mpt_intr(mpt);
		}
	}
	req->state &= ~REQ_STATE_NEED_WAKEUP;
	if (mpt->reset_cnt != saved_cnt) {
		return (EIO);
	}
	if (time_ms && timeout <= 0) {
		MSG_REQUEST_HEADER *msg_hdr = req->req_vbuf;
		req->state |= REQ_STATE_TIMEDOUT;
		mpt_prt(mpt, "mpt_wait_req(%x) timed out\n", msg_hdr->Function);
		return (ETIMEDOUT);
	}
	return (0);
}