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
struct bufferevent {int /*<<< orphan*/  ev_base; int /*<<< orphan*/  ev_read; } ;

/* Variables and functions */
 int event_base_get_npriorities (int /*<<< orphan*/ ) ; 
 int event_get_priority (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 

int
bufferevent_get_priority(const struct bufferevent *bufev)
{
	if (event_initialized(&bufev->ev_read)) {
		return event_get_priority(&bufev->ev_read);
	} else {
		return event_base_get_npriorities(bufev->ev_base) / 2;
	}
}