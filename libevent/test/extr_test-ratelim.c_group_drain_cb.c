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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_rate_limit_group_decrement_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_rate_limit_group_decrement_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_group_drain ; 
 int /*<<< orphan*/  ratelim_group ; 

__attribute__((used)) static void
group_drain_cb(evutil_socket_t fd, short events, void *arg)
{
	bufferevent_rate_limit_group_decrement_read(ratelim_group, cfg_group_drain);
	bufferevent_rate_limit_group_decrement_write(ratelim_group, cfg_group_drain);
}