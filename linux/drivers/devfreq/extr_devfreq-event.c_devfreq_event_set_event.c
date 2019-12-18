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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_event ) (struct devfreq_event_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  devfreq_event_is_enabled (struct devfreq_event_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq_event_dev*) ; 

int devfreq_event_set_event(struct devfreq_event_dev *edev)
{
	int ret;

	if (!edev || !edev->desc)
		return -EINVAL;

	if (!edev->desc->ops || !edev->desc->ops->set_event)
		return -EINVAL;

	if (!devfreq_event_is_enabled(edev))
		return -EPERM;

	mutex_lock(&edev->lock);
	ret = edev->desc->ops->set_event(edev);
	mutex_unlock(&edev->lock);

	return ret;
}