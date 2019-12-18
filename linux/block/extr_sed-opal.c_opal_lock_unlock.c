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
struct TYPE_2__ {scalar_t__ who; } ;
struct opal_lock_unlock {TYPE_1__ session; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OPAL_USER9 ; 
 int __opal_lock_unlock (struct opal_dev*,struct opal_lock_unlock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opal_lock_unlock(struct opal_dev *dev,
			    struct opal_lock_unlock *lk_unlk)
{
	int ret;

	if (lk_unlk->session.who > OPAL_USER9)
		return -EINVAL;

	mutex_lock(&dev->dev_lock);
	ret = __opal_lock_unlock(dev, lk_unlk);
	mutex_unlock(&dev->dev_lock);

	return ret;
}