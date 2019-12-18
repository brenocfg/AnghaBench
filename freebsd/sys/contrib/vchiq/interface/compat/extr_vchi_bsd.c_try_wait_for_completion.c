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
struct completion {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
try_wait_for_completion(struct completion *c)
{
	int res = 0;

	mtx_lock(&c->lock);
	if (!c->done)
		res = 1;
	else
		c->done--;
	mtx_unlock(&c->lock);
	return res == 0;
}