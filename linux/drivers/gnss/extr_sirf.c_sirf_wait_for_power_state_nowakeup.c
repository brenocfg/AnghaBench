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
struct sirf_data {int active; int /*<<< orphan*/  power_wait; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SIRF_REPORT_CYCLE ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sirf_wait_for_power_state_nowakeup(struct sirf_data *data,
						bool active,
						unsigned long timeout)
{
	int ret;

	/* Wait for state change (including any shutdown messages). */
	msleep(timeout);

	/* Wait for data reception or timeout. */
	data->active = false;
	ret = wait_event_interruptible_timeout(data->power_wait,
			data->active, msecs_to_jiffies(SIRF_REPORT_CYCLE));
	if (ret < 0)
		return ret;

	if (ret > 0 && !active)
		return -ETIMEDOUT;

	if (ret == 0 && active)
		return -ETIMEDOUT;

	return 0;
}