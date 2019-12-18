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
struct timeval {int /*<<< orphan*/  tv_usec; } ;
struct event {struct timeval ev_timeout; } ;
struct common_timeout_list {int /*<<< orphan*/  timeout_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROSECONDS_MASK ; 
 int /*<<< orphan*/  event_add_nolock_ (int /*<<< orphan*/ *,struct timeval*,int) ; 

__attribute__((used)) static void
common_timeout_schedule(struct common_timeout_list *ctl,
    const struct timeval *now, struct event *head)
{
	struct timeval timeout = head->ev_timeout;
	timeout.tv_usec &= MICROSECONDS_MASK;
	event_add_nolock_(&ctl->timeout_event, &timeout, 1);
}