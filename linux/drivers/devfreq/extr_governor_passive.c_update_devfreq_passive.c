#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct devfreq {unsigned long previous_freq; int /*<<< orphan*/  lock; TYPE_3__ dev; TYPE_1__* profile; TYPE_2__* governor; } ;
struct TYPE_5__ {int (* get_target_freq ) (struct devfreq*,unsigned long*) ;} ;
struct TYPE_4__ {int (* target ) (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ;scalar_t__ freq_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 scalar_t__ devfreq_update_status (struct devfreq*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq*,unsigned long*) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_devfreq_passive(struct devfreq *devfreq, unsigned long freq)
{
	int ret;

	if (!devfreq->governor)
		return -EINVAL;

	mutex_lock_nested(&devfreq->lock, SINGLE_DEPTH_NESTING);

	ret = devfreq->governor->get_target_freq(devfreq, &freq);
	if (ret < 0)
		goto out;

	ret = devfreq->profile->target(devfreq->dev.parent, &freq, 0);
	if (ret < 0)
		goto out;

	if (devfreq->profile->freq_table
		&& (devfreq_update_status(devfreq, freq)))
		dev_err(&devfreq->dev,
			"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = freq;

out:
	mutex_unlock(&devfreq->lock);

	return 0;
}