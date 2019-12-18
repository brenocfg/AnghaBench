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
struct bufferevent_async {int ok; } ;
struct bufferevent {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_async_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 struct bufferevent_async* upcast (struct bufferevent*) ; 

void
bufferevent_async_set_connected_(struct bufferevent *bev)
{
	struct bufferevent_async *bev_async = upcast(bev);
	bev_async->ok = 1;
	/* Now's a good time to consider reading/writing */
	be_async_enable(bev, bev->enabled);
}