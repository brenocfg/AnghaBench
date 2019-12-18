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
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
down(struct semaphore *s)
{

	mtx_lock(&s->mtx);
	while (s->value == 0) {
		s->waiters++;
		cv_wait(&s->cv, &s->mtx);
		s->waiters--;
	}

	s->value--;
	mtx_unlock(&s->mtx);
}