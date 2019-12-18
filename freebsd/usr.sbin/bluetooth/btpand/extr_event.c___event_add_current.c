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
struct event {int flags; } ;

/* Variables and functions */
 int EV_CURRENT ; 
 int EV_PENDING ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
__event_add_current(struct event *ev)
{
	assert((ev->flags & (EV_PENDING|EV_CURRENT)) == 0);

	TAILQ_INSERT_TAIL(&current, ev, next);
	ev->flags |= EV_CURRENT;
}