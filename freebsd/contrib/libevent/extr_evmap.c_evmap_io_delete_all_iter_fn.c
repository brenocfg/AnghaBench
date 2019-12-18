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
struct evmap_io {int /*<<< orphan*/  events; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int delete_all_in_dlist (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evmap_io_delete_all_iter_fn(struct event_base *base, evutil_socket_t fd,
    struct evmap_io *io_info, void *arg)
{
	return delete_all_in_dlist(&io_info->events);
}