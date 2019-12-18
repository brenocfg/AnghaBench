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
struct semaphore {scalar_t__ value; int /*<<< orphan*/  mtx; int /*<<< orphan*/  waiters; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
down_interruptible(struct semaphore *s)
{
	int ret ;

	ret = 0;

	mtx_lock(&s->mtx);

	while (s->value == 0) {
		s->waiters++;
		ret = cv_wait_sig(&s->cv, &s->mtx);
		s->waiters--;

		if (ret == EINTR) {
			mtx_unlock(&s->mtx);
			return (-EINTR);
		}

		if (ret == ERESTART)
			continue;
	}

	s->value--;
	mtx_unlock(&s->mtx);

	return (0);
}