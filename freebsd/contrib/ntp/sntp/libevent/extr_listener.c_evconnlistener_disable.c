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
struct evconnlistener {TYPE_1__* ops; scalar_t__ enabled; } ;
struct TYPE_2__ {int (* disable ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int stub1 (struct evconnlistener*) ; 

int
evconnlistener_disable(struct evconnlistener *lev)
{
	int r;
	LOCK(lev);
	lev->enabled = 0;
	r = lev->ops->disable(lev);
	UNLOCK(lev);
	return r;
}