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
struct bufferevent_rate_limit_group {scalar_t__ n_members; int /*<<< orphan*/  lock; int /*<<< orphan*/  master_refill_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  LOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  UNLOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct bufferevent_rate_limit_group*) ; 

void
bufferevent_rate_limit_group_free(struct bufferevent_rate_limit_group *g)
{
	LOCK_GROUP(g);
	EVUTIL_ASSERT(0 == g->n_members);
	event_del(&g->master_refill_event);
	UNLOCK_GROUP(g);
	EVTHREAD_FREE_LOCK(g->lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	mm_free(g);
}