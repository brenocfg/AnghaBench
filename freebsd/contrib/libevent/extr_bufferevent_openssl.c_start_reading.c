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
struct bufferevent {int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  ev_read; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_openssl {scalar_t__ read_blocked_on_write; TYPE_1__ bev; scalar_t__ underlying; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_SUSPEND_FILT_READ ; 
 int bufferevent_add_event_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_read_ (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
start_reading(struct bufferevent_openssl *bev_ssl)
{
	if (bev_ssl->underlying) {
		bufferevent_unsuspend_read_(bev_ssl->underlying,
		    BEV_SUSPEND_FILT_READ);
		return 0;
	} else {
		struct bufferevent *bev = &bev_ssl->bev.bev;
		int r;
		r = bufferevent_add_event_(&bev->ev_read, &bev->timeout_read);
		if (r == 0 && bev_ssl->read_blocked_on_write)
			r = bufferevent_add_event_(&bev->ev_write,
			    &bev->timeout_write);
		return r;
	}
}