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
struct timeval {int dummy; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct mqueue_msg {int dummy; } ;
struct mqueue {size_t mq_msgsize; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ETIMEDOUT ; 
 unsigned int MQ_PRIO_MAX ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int _mqueue_send (struct mqueue*,struct mqueue_msg*,int) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  mqueue_freemsg (struct mqueue_msg*) ; 
 struct mqueue_msg* mqueue_loadmsg (char const*,size_t,unsigned int) ; 
 int /*<<< orphan*/  timespecsub (struct timespec const*,struct timespec*,struct timespec*) ; 
 int tvtohz (struct timeval*) ; 

int
mqueue_send(struct mqueue *mq, const char *msg_ptr,
	size_t msg_len, unsigned msg_prio, int waitok,
	const struct timespec *abs_timeout)
{
	struct mqueue_msg *msg;
	struct timespec ts, ts2;
	struct timeval tv;
	int error;

	if (msg_prio >= MQ_PRIO_MAX)
		return (EINVAL);
	if (msg_len > mq->mq_msgsize)
		return (EMSGSIZE);
	msg = mqueue_loadmsg(msg_ptr, msg_len, msg_prio);
	if (msg == NULL)
		return (EFAULT);

	/* O_NONBLOCK case */
	if (!waitok) {
		error = _mqueue_send(mq, msg, -1);
		if (error)
			goto bad;
		return (0);
	}

	/* we allow a null timeout (wait forever) */
	if (abs_timeout == NULL) {
		error = _mqueue_send(mq, msg, 0);
		if (error)
			goto bad;
		return (0);
	}

	/* send it before checking time */
	error = _mqueue_send(mq, msg, -1);
	if (error == 0)
		return (0);

	if (error != EAGAIN)
		goto bad;

	if (abs_timeout->tv_nsec >= 1000000000 || abs_timeout->tv_nsec < 0) {
		error = EINVAL;
		goto bad;
	}
	for (;;) {
		getnanotime(&ts);
		timespecsub(abs_timeout, &ts, &ts2);
		if (ts2.tv_sec < 0 || (ts2.tv_sec == 0 && ts2.tv_nsec <= 0)) {
			error = ETIMEDOUT;
			break;
		}
		TIMESPEC_TO_TIMEVAL(&tv, &ts2);
		error = _mqueue_send(mq, msg, tvtohz(&tv));
		if (error != ETIMEDOUT)
			break;
	}
	if (error == 0)
		return (0);
bad:
	mqueue_freemsg(msg);
	return (error);
}