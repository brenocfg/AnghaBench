#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  config; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int ecctr (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hw_perf_event_reset(struct perf_event *event)
{
	u64 prev, new;
	int err;

	do {
		prev = local64_read(&event->hw.prev_count);
		err = ecctr(event->hw.config, &new);
		if (err) {
			if (err != 3)
				break;
			/* The counter is not (yet) available. This
			 * might happen if the counter set to which
			 * this counter belongs is in the disabled
			 * state.
			 */
			new = 0;
		}
	} while (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	return err;
}