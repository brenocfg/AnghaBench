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
struct foreach_helper {int count; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 scalar_t__ event_get_callback (struct event const*) ; 
 struct foreach_helper* event_get_callback_arg (struct event const*) ; 
 scalar_t__ timeout_cb ; 

__attribute__((used)) static int
foreach_find_cb(const struct event_base *base, const struct event *ev, void *arg)
{
	const struct event **ev_out = arg;
	struct foreach_helper *h = event_get_callback_arg(ev);
	if (event_get_callback(ev) != timeout_cb)
		return 0;
	if (h->count == 99) {
		*ev_out = ev;
		return 101;
	}
	return 0;
}