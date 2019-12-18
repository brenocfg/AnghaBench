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
struct evconnlistener {int enabled; TYPE_1__* ops; scalar_t__ cb; } ;
struct TYPE_2__ {int (* enable ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int stub1 (struct evconnlistener*) ; 

int
evconnlistener_enable(struct evconnlistener *lev)
{
	int r;
	LOCK(lev);
	lev->enabled = 1;
	if (lev->cb)
		r = lev->ops->enable(lev);
	else
		r = 0;
	UNLOCK(lev);
	return r;
}