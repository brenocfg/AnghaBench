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
struct completion {scalar_t__ done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  _completion_claim (struct completion*) ; 
 int cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
wait_for_completion_interruptible_timeout(struct completion *c, unsigned long timeout)
{
	int res = 0;
	unsigned long start, now;
	start = jiffies;

	mtx_lock(&c->lock);
	while (c->done == 0) {
		res = cv_timedwait_sig(&c->cv, &c->lock, timeout);
		if (res)
			goto out;
		now = jiffies;
		if (timeout < (now - start)) {
			res = EWOULDBLOCK;
			goto out;
		}

		timeout -= (now - start);
		start = now;
	}

	_completion_claim(c);
	res = 0;

out:
	mtx_unlock(&c->lock);

	if (res == EWOULDBLOCK) {
		return 0;
	} else if ((res == EINTR) || (res == ERESTART)) {
		return -ERESTART;
	} else {
		KASSERT((res == 0), ("res = %d", res));
		return timeout;
	}
}