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
struct TYPE_3__ {int /*<<< orphan*/  lr; } ;
struct TYPE_4__ {TYPE_1__ opal_key; } ;
struct opal_lock_unlock {TYPE_2__ session; } ;
struct opal_suspend_data {int /*<<< orphan*/  lr; struct opal_lock_unlock unlk; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_suspend_info (struct opal_dev*,struct opal_suspend_data*) ; 
 struct opal_suspend_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 

__attribute__((used)) static int opal_save(struct opal_dev *dev, struct opal_lock_unlock *lk_unlk)
{
	struct opal_suspend_data *suspend;

	suspend = kzalloc(sizeof(*suspend), GFP_KERNEL);
	if (!suspend)
		return -ENOMEM;

	suspend->unlk = *lk_unlk;
	suspend->lr = lk_unlk->session.opal_key.lr;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	add_suspend_info(dev, suspend);
	mutex_unlock(&dev->dev_lock);

	return 0;
}