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
struct mqueue_msg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct mqueue {TYPE_1__ mq_wsel; TYPE_1__ mq_rsel; int /*<<< orphan*/  mq_mutex; int /*<<< orphan*/  mq_msgq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MQUEUEDATA ; 
 struct mqueue_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mqueue_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  curmq ; 
 int /*<<< orphan*/  free (struct mqueue_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqueue_zone ; 
 int /*<<< orphan*/  msg_link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mqueue*) ; 

__attribute__((used)) static void
mqueue_free(struct mqueue *mq)
{
	struct mqueue_msg *msg;

	while ((msg = TAILQ_FIRST(&mq->mq_msgq)) != NULL) {
		TAILQ_REMOVE(&mq->mq_msgq, msg, msg_link);
		free(msg, M_MQUEUEDATA);
	}

	mtx_destroy(&mq->mq_mutex);
	seldrain(&mq->mq_rsel);
	seldrain(&mq->mq_wsel);
	knlist_destroy(&mq->mq_rsel.si_note);
	knlist_destroy(&mq->mq_wsel.si_note);
	uma_zfree(mqueue_zone, mq);
	atomic_add_int(&curmq, -1);
}