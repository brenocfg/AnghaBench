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
struct bufferevent_filtered {int /*<<< orphan*/  underlying; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_RESET_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_SUSPEND_FILT_READ ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_unsuspend_read_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bufferevent_filtered* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_filter_enable(struct bufferevent *bev, short event)
{
	struct bufferevent_filtered *bevf = upcast(bev);
	if (event & EV_WRITE)
		BEV_RESET_GENERIC_WRITE_TIMEOUT(bev);

	if (event & EV_READ) {
		BEV_RESET_GENERIC_READ_TIMEOUT(bev);
		bufferevent_unsuspend_read_(bevf->underlying,
		    BEV_SUSPEND_FILT_READ);
	}
	return 0;
}