#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct event_base {int dummy; } ;
struct evconnlistener {TYPE_1__* ops; } ;
struct TYPE_2__ {struct event_base* (* getbase ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 struct event_base* stub1 (struct evconnlistener*) ; 

struct event_base *
evconnlistener_get_base(struct evconnlistener *lev)
{
	struct event_base *base;
	LOCK(lev);
	base = lev->ops->getbase(lev);
	UNLOCK(lev);
	return base;
}