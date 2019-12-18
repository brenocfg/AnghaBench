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
struct timeval {int dummy; } ;
struct event {int flags; struct timeval timeout; int /*<<< orphan*/  expire; } ;

/* Variables and functions */
 int EV_CURRENT ; 
 int EV_HAS_TIMEOUT ; 
 int EV_PENDING ; 
 int /*<<< orphan*/  __event_link (struct event*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tv_add (int /*<<< orphan*/ *,struct timeval const*) ; 

int
__event_add(struct event *ev, const struct timeval *timeout)
{
	assert((ev->flags & (EV_PENDING|EV_CURRENT)) == 0);

	if (timeout != NULL) {
		gettimeofday(&ev->expire, NULL);
		tv_add(&ev->expire, timeout);
		ev->timeout = *timeout;
		ev->flags |= EV_HAS_TIMEOUT;
	} else
		ev->flags &= ~EV_HAS_TIMEOUT;

	__event_link(ev);

	return (0);
}