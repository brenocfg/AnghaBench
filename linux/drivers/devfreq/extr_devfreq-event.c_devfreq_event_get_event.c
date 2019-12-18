#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct devfreq_event_dev {int /*<<< orphan*/  lock; TYPE_2__* desc; } ;
struct devfreq_event_data {scalar_t__ load_count; scalar_t__ total_count; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_event ) (struct devfreq_event_dev*,struct devfreq_event_data*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  devfreq_event_is_enabled (struct devfreq_event_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq_event_dev*,struct devfreq_event_data*) ; 

int devfreq_event_get_event(struct devfreq_event_dev *edev,
			    struct devfreq_event_data *edata)
{
	int ret;

	if (!edev || !edev->desc)
		return -EINVAL;

	if (!edev->desc->ops || !edev->desc->ops->get_event)
		return -EINVAL;

	if (!devfreq_event_is_enabled(edev))
		return -EINVAL;

	edata->total_count = edata->load_count = 0;

	mutex_lock(&edev->lock);
	ret = edev->desc->ops->get_event(edev, edata);
	if (ret < 0)
		edata->total_count = edata->load_count = 0;
	mutex_unlock(&edev->lock);

	return ret;
}