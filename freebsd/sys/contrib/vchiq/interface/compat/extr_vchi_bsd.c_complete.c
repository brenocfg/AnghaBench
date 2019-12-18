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
struct completion {int done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
complete(struct completion *c)
{
	mtx_lock(&c->lock);

	if (c->done >= 0) {
		KASSERT(c->done < INT_MAX, ("c->done overflow")); /* XXX check */
		c->done++;
		cv_signal(&c->cv);
	} else {
		KASSERT(c->done == -1, ("Invalid value of c->done: %d", c->done));
	}

	mtx_unlock(&c->lock);
}