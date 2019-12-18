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
struct evconnlistener {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* getfd ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  stub1 (struct evconnlistener*) ; 

evutil_socket_t
evconnlistener_get_fd(struct evconnlistener *lev)
{
	evutil_socket_t fd;
	LOCK(lev);
	fd = lev->ops->getfd(lev);
	UNLOCK(lev);
	return fd;
}