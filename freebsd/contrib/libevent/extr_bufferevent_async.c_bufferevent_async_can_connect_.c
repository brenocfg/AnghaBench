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
struct win32_extension_fns {scalar_t__ ConnectEx; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; } ;

/* Variables and functions */
 scalar_t__ BEV_IS_ASYNC (struct bufferevent*) ; 
 scalar_t__ event_base_get_iocp_ (int /*<<< orphan*/ ) ; 
 struct win32_extension_fns* event_get_win32_extension_fns_ () ; 

int
bufferevent_async_can_connect_(struct bufferevent *bev)
{
	const struct win32_extension_fns *ext =
	    event_get_win32_extension_fns_();

	if (BEV_IS_ASYNC(bev) &&
	    event_base_get_iocp_(bev->ev_base) &&
	    ext && ext->ConnectEx)
		return 1;

	return 0;
}