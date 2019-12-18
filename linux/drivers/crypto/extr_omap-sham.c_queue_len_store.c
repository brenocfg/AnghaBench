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
struct TYPE_2__ {long max_qlen; } ;
struct omap_sham_dev {int /*<<< orphan*/  lock; TYPE_1__ queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct omap_sham_dev* dev_get_drvdata (struct device*) ; 
 size_t kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t queue_len_store(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t size)
{
	struct omap_sham_dev *dd = dev_get_drvdata(dev);
	ssize_t status;
	long value;
	unsigned long flags;

	status = kstrtol(buf, 0, &value);
	if (status)
		return status;

	if (value < 1)
		return -EINVAL;

	/*
	 * Changing the queue size in fly is safe, if size becomes smaller
	 * than current size, it will just not accept new entries until
	 * it has shrank enough.
	 */
	spin_lock_irqsave(&dd->lock, flags);
	dd->queue.max_qlen = value;
	spin_unlock_irqrestore(&dd->lock, flags);

	return size;
}