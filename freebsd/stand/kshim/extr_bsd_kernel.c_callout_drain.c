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
struct callout {int /*<<< orphan*/ * mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (struct callout*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
callout_drain(struct callout *c)
{
	if (c->mtx == NULL)
		return;			/* not initialised */

	mtx_lock(c->mtx);
	callout_stop(c);
	mtx_unlock(c->mtx);
}