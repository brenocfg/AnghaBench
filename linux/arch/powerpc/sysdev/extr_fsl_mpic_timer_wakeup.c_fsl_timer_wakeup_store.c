#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time64_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_7__ {TYPE_1__* timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_mpic_timer_irq ; 
 TYPE_3__* fsl_wakeup ; 
 scalar_t__ kstrtoll (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpic_free_timer (TYPE_1__*) ; 
 TYPE_1__* mpic_request_timer (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpic_start_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_lock ; 

__attribute__((used)) static ssize_t fsl_timer_wakeup_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf,
				size_t count)
{
	time64_t interval;
	int ret;

	if (kstrtoll(buf, 0, &interval))
		return -EINVAL;

	mutex_lock(&sysfs_lock);

	if (fsl_wakeup->timer) {
		disable_irq_wake(fsl_wakeup->timer->irq);
		mpic_free_timer(fsl_wakeup->timer);
		fsl_wakeup->timer = NULL;
	}

	if (!interval) {
		mutex_unlock(&sysfs_lock);
		return count;
	}

	fsl_wakeup->timer = mpic_request_timer(fsl_mpic_timer_irq,
						fsl_wakeup, interval);
	if (!fsl_wakeup->timer) {
		mutex_unlock(&sysfs_lock);
		return -EINVAL;
	}

	ret = enable_irq_wake(fsl_wakeup->timer->irq);
	if (ret) {
		mpic_free_timer(fsl_wakeup->timer);
		fsl_wakeup->timer = NULL;
		mutex_unlock(&sysfs_lock);

		return ret;
	}

	mpic_start_timer(fsl_wakeup->timer);

	mutex_unlock(&sysfs_lock);

	return count;
}