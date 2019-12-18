#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mqueue_msg {scalar_t__ msg_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct mqueue {scalar_t__ mq_receivers; int mq_flags; int /*<<< orphan*/  mq_mutex; int /*<<< orphan*/  mq_msgq; int /*<<< orphan*/ * mq_notifier; TYPE_1__ mq_wsel; scalar_t__ mq_senders; int /*<<< orphan*/  mq_totalbytes; int /*<<< orphan*/  mq_curmsgs; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MQ_WSEL ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct mqueue_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mqueue_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqueue_send_notification (struct mqueue*) ; 
 int /*<<< orphan*/  msg_link ; 
 int msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup_one (scalar_t__*) ; 

__attribute__((used)) static int
_mqueue_recv(struct mqueue *mq, struct mqueue_msg **msg, int timo)
{	
	int error = 0;
	
	mtx_lock(&mq->mq_mutex);
	while ((*msg = TAILQ_FIRST(&mq->mq_msgq)) == NULL && error == 0) {
		if (timo < 0) {
			mtx_unlock(&mq->mq_mutex);
			return (EAGAIN);
		}
		mq->mq_receivers++;
		error = msleep(&mq->mq_receivers, &mq->mq_mutex,
			    PCATCH, "mqrecv", timo);
		mq->mq_receivers--;
		if (error == EAGAIN)
			error = ETIMEDOUT;
	}
	if (*msg != NULL) {
		error = 0;
		TAILQ_REMOVE(&mq->mq_msgq, *msg, msg_link);
		mq->mq_curmsgs--;
		mq->mq_totalbytes -= (*msg)->msg_size;
		if (mq->mq_senders)
			wakeup_one(&mq->mq_senders);
		if (mq->mq_flags & MQ_WSEL) {
			mq->mq_flags &= ~MQ_WSEL;
			selwakeup(&mq->mq_wsel);
		}
		KNOTE_LOCKED(&mq->mq_wsel.si_note, 0);
	}
	if (mq->mq_notifier != NULL && mq->mq_receivers == 0 &&
	    !TAILQ_EMPTY(&mq->mq_msgq)) {
		mqueue_send_notification(mq);
	}
	mtx_unlock(&mq->mq_mutex);
	return (error);
}