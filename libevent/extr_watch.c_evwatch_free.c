#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct evwatch {size_t type; TYPE_1__* base; } ;
struct TYPE_3__ {int /*<<< orphan*/ * watchers; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evwatch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evwatch*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  th_base_lock ; 

void
evwatch_free(struct evwatch *watcher)
{
	EVBASE_ACQUIRE_LOCK(watcher->base, th_base_lock);
	TAILQ_REMOVE(&watcher->base->watchers[watcher->type], watcher, next);
	EVBASE_RELEASE_LOCK(watcher->base, th_base_lock);
	mm_free(watcher);
}