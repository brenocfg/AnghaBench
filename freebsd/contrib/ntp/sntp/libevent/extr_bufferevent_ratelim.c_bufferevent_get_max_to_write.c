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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_write_max_ (int /*<<< orphan*/ ) ; 

ev_ssize_t
bufferevent_get_max_to_write(struct bufferevent *bev)
{
	ev_ssize_t r;
	BEV_LOCK(bev);
	r = bufferevent_get_write_max_(BEV_UPCAST(bev));
	BEV_UNLOCK(bev);
	return r;
}