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
struct semaphore {scalar_t__ value; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
down_trylock(struct semaphore *s)
{
	int ret;

	ret = 0;

	mtx_lock(&s->mtx);

	if (s->value > 0) {
		/* Success. */
		s->value--;
		ret = 0;
	} else {
		ret = -EAGAIN;
	}

	mtx_unlock(&s->mtx);

	return (ret);
}