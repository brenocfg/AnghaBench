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
struct completion {scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEPQ_SLEEP ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int sleepq_broadcast (struct completion*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (struct completion*) ; 
 int /*<<< orphan*/  sleepq_release (struct completion*) ; 
 int sleepq_signal (struct completion*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
linux_complete_common(struct completion *c, int all)
{
	int wakeup_swapper;

	sleepq_lock(c);
	if (all) {
		c->done = UINT_MAX;
		wakeup_swapper = sleepq_broadcast(c, SLEEPQ_SLEEP, 0, 0);
	} else {
		if (c->done != UINT_MAX)
			c->done++;
		wakeup_swapper = sleepq_signal(c, SLEEPQ_SLEEP, 0, 0);
	}
	sleepq_release(c);
	if (wakeup_swapper)
		kick_proc0();
}