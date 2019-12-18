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
struct devfreq_event_dev {scalar_t__ enable_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool devfreq_event_is_enabled(struct devfreq_event_dev *edev)
{
	bool enabled = false;

	if (!edev || !edev->desc)
		return enabled;

	mutex_lock(&edev->lock);

	if (edev->enable_count > 0)
		enabled = true;

	mutex_unlock(&edev->lock);

	return enabled;
}