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
struct bufferevent {int /*<<< orphan*/  ev_read; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_openssl {TYPE_1__ bev; scalar_t__ underlying; scalar_t__ write_blocked_on_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_SUSPEND_FILT_READ ; 
 int /*<<< orphan*/  bufferevent_suspend_read_ (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stop_reading(struct bufferevent_openssl *bev_ssl)
{
	if (bev_ssl->write_blocked_on_read)
		return;
	if (bev_ssl->underlying) {
		bufferevent_suspend_read_(bev_ssl->underlying,
		    BEV_SUSPEND_FILT_READ);
	} else {
		struct bufferevent *bev = &bev_ssl->bev.bev;
		event_del(&bev->ev_read);
	}
}