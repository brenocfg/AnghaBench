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
struct sirf_data {int active; TYPE_1__* serdev; int /*<<< orphan*/  power_wait; int /*<<< orphan*/  wakeup; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int sirf_wait_for_power_state_nowakeup (struct sirf_data*,int,unsigned long) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sirf_wait_for_power_state(struct sirf_data *data, bool active,
					unsigned long timeout)
{
	int ret;

	if (!data->wakeup)
		return sirf_wait_for_power_state_nowakeup(data, active, timeout);

	ret = wait_event_interruptible_timeout(data->power_wait,
			data->active == active, msecs_to_jiffies(timeout));
	if (ret < 0)
		return ret;

	if (ret == 0) {
		dev_warn(&data->serdev->dev, "timeout waiting for active state = %d\n",
				active);
		return -ETIMEDOUT;
	}

	return 0;
}