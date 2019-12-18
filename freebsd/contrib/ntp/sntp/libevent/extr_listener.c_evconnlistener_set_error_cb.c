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
struct evconnlistener {int /*<<< orphan*/  errorcb; } ;
typedef  int /*<<< orphan*/  evconnlistener_errorcb ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 

void
evconnlistener_set_error_cb(struct evconnlistener *lev,
    evconnlistener_errorcb errorcb)
{
	LOCK(lev);
	lev->errorcb = errorcb;
	UNLOCK(lev);
}