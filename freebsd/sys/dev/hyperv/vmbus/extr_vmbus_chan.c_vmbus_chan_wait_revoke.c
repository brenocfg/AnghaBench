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
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int WAIT_COUNT ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ vmbus_chan_is_revoked (struct vmbus_channel const*) ; 

__attribute__((used)) static bool
vmbus_chan_wait_revoke(const struct vmbus_channel *chan, bool can_sleep)
{
#define WAIT_COUNT	200	/* 200ms */

	int i;

	for (i = 0; i < WAIT_COUNT; ++i) {
		if (vmbus_chan_is_revoked(chan))
			return (true);
		if (can_sleep)
			pause("wchrev", 1);
		else
			DELAY(1000);
	}
	return (false);

#undef WAIT_COUNT
}