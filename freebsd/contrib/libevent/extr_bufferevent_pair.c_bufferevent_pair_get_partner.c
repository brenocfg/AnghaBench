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
struct bufferevent_pair {scalar_t__ partner; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decref_and_unlock (struct bufferevent*) ; 
 struct bufferevent* downcast (scalar_t__) ; 
 int /*<<< orphan*/  incref_and_lock (struct bufferevent*) ; 
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

struct bufferevent *
bufferevent_pair_get_partner(struct bufferevent *bev)
{
	struct bufferevent_pair *bev_p;
	struct bufferevent *partner = NULL;
	bev_p = upcast(bev);
	if (! bev_p)
		return NULL;

	incref_and_lock(bev);
	if (bev_p->partner)
		partner = downcast(bev_p->partner);
	decref_and_unlock(bev);
	return partner;
}