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
struct callout {void (* c_func ) (void*) ;scalar_t__ timeout; void* c_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct callout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (struct callout*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  head_callout ; 
 int /*<<< orphan*/  mtx_callout ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 

void
callout_reset(struct callout *c, int to_ticks,
    void (*func) (void *), void *arg)
{
	callout_stop(c);

	c->c_func = func;
	c->c_arg = arg;
	c->timeout = ticks + to_ticks;

	mtx_lock(&mtx_callout);
	LIST_INSERT_HEAD(&head_callout, c, entry);
	mtx_unlock(&mtx_callout);
}