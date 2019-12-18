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
typedef  int /*<<< orphan*/  u32 ;
struct devfreq {int /*<<< orphan*/  min_freq; int /*<<< orphan*/  scaling_min_freq; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  scaling_max_freq; TYPE_1__* governor; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int (* get_target_freq ) (struct devfreq*,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_FLAG_LEAST_UPPER_BOUND ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int devfreq_set_target (struct devfreq*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq*,unsigned long*) ; 

int update_devfreq(struct devfreq *devfreq)
{
	unsigned long freq, min_freq, max_freq;
	int err = 0;
	u32 flags = 0;

	if (!mutex_is_locked(&devfreq->lock)) {
		WARN(true, "devfreq->lock must be locked by the caller.\n");
		return -EINVAL;
	}

	if (!devfreq->governor)
		return -EINVAL;

	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq);
	if (err)
		return err;

	/*
	 * Adjust the frequency with user freq, QoS and available freq.
	 *
	 * List from the highest priority
	 * max_freq
	 * min_freq
	 */
	max_freq = min(devfreq->scaling_max_freq, devfreq->max_freq);
	min_freq = max(devfreq->scaling_min_freq, devfreq->min_freq);

	if (freq < min_freq) {
		freq = min_freq;
		flags &= ~DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use GLB */
	}
	if (freq > max_freq) {
		freq = max_freq;
		flags |= DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use LUB */
	}

	return devfreq_set_target(devfreq, freq, flags);

}