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
struct evconnlistener {TYPE_1__* ops; int /*<<< orphan*/ * errorcb; int /*<<< orphan*/ * cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  listener_decref_and_unlock (struct evconnlistener*) ; 
 int /*<<< orphan*/  stub1 (struct evconnlistener*) ; 

void
evconnlistener_free(struct evconnlistener *lev)
{
	LOCK(lev);
	lev->cb = NULL;
	lev->errorcb = NULL;
	if (lev->ops->shutdown)
		lev->ops->shutdown(lev);
	listener_decref_and_unlock(lev);
}