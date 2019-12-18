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
struct completion {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
wait_for_completion(struct completion *c)
{
	mtx_lock(&c->lock);
	if (!c->done)
		cv_wait(&c->cv, &c->lock);
	c->done--;
	mtx_unlock(&c->lock);
}