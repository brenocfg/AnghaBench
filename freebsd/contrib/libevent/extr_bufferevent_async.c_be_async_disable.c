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
struct bufferevent_async {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_DEL_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_DEL_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  bev_async_del_read (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bev_async_del_write (struct bufferevent_async*) ; 
 struct bufferevent_async* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_async_disable(struct bufferevent *bev, short what)
{
	struct bufferevent_async *bev_async = upcast(bev);
	/* XXXX If we disable reading or writing, we may want to consider
	 * canceling any in-progress read or write operation, though it might
	 * not work. */

	if (what & EV_READ) {
		BEV_DEL_GENERIC_READ_TIMEOUT(bev);
		bev_async_del_read(bev_async);
	}
	if (what & EV_WRITE) {
		BEV_DEL_GENERIC_WRITE_TIMEOUT(bev);
		bev_async_del_write(bev_async);
	}

	return 0;
}