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
struct evconnlistener {void* user_data; scalar_t__ cb; scalar_t__ enabled; } ;
typedef  scalar_t__ evconnlistener_cb ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  evconnlistener_enable (struct evconnlistener*) ; 

void
evconnlistener_set_cb(struct evconnlistener *lev,
    evconnlistener_cb cb, void *arg)
{
	int enable = 0;
	LOCK(lev);
	if (lev->enabled && !lev->cb)
		enable = 1;
	lev->cb = cb;
	lev->user_data = arg;
	if (enable)
		evconnlistener_enable(lev);
	UNLOCK(lev);
}