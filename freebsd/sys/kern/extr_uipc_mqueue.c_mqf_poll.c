#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mqueue {scalar_t__ mq_curmsgs; scalar_t__ mq_maxmsg; int /*<<< orphan*/  mq_mutex; int /*<<< orphan*/  mq_wsel; int /*<<< orphan*/  mq_flags; int /*<<< orphan*/  mq_rsel; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct mqueue* FPTOMQ (struct file*) ; 
 int /*<<< orphan*/  MQ_RSEL ; 
 int /*<<< orphan*/  MQ_WSEL ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqf_poll(struct file *fp, int events, struct ucred *active_cred,
	struct thread *td)
{
	struct mqueue *mq = FPTOMQ(fp);
	int revents = 0;

	mtx_lock(&mq->mq_mutex);
	if (events & (POLLIN | POLLRDNORM)) {
		if (mq->mq_curmsgs) {
			revents |= events & (POLLIN | POLLRDNORM);
		} else {
			mq->mq_flags |= MQ_RSEL;
			selrecord(td, &mq->mq_rsel);
 		}
	}
	if (events & POLLOUT) {
		if (mq->mq_curmsgs < mq->mq_maxmsg)
			revents |= POLLOUT;
		else {
			mq->mq_flags |= MQ_WSEL;
			selrecord(td, &mq->mq_wsel);
		}
	}
	mtx_unlock(&mq->mq_mutex);
	return (revents);
}