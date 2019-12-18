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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_single_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 TYPE_1__* BEV_UPCAST (struct bufferevent*) ; 

ev_ssize_t
bufferevent_get_max_single_read(struct bufferevent *bev)
{
	ev_ssize_t r;

	BEV_LOCK(bev);
	r = BEV_UPCAST(bev)->max_single_read;
	BEV_UNLOCK(bev);
	return r;
}