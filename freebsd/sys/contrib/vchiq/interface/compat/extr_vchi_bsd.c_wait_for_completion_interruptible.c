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
 int /*<<< orphan*/  _completion_claim (struct completion*) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
wait_for_completion_interruptible(struct completion *c)
{
	int res = 0;

	mtx_lock(&c->lock);
	while (c->done == 0) {
		res = cv_wait_sig(&c->cv, &c->lock);
		if (res)
			goto out;
	}

	_completion_claim(c);

out:
	mtx_unlock(&c->lock);

	if ((res == EINTR) || (res == ERESTART))
		res = -ERESTART;
	return res;
}