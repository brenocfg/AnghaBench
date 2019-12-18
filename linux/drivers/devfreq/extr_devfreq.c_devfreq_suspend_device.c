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
struct devfreq {scalar_t__ suspend_freq; TYPE_1__* governor; int /*<<< orphan*/  suspend_count; } ;
struct TYPE_2__ {int (* event_handler ) (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_SUSPEND ; 
 int EINVAL ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int devfreq_set_target (struct devfreq*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int devfreq_suspend_device(struct devfreq *devfreq)
{
	int ret;

	if (!devfreq)
		return -EINVAL;

	if (atomic_inc_return(&devfreq->suspend_count) > 1)
		return 0;

	if (devfreq->governor) {
		ret = devfreq->governor->event_handler(devfreq,
					DEVFREQ_GOV_SUSPEND, NULL);
		if (ret)
			return ret;
	}

	if (devfreq->suspend_freq) {
		ret = devfreq_set_target(devfreq, devfreq->suspend_freq, 0);
		if (ret)
			return ret;
	}

	return 0;
}