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
struct notifier_block {int dummy; } ;
struct extcon_dev_notifier_devres {unsigned int id; struct notifier_block* nb; struct extcon_dev* edev; } ;
struct extcon_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_extcon_dev_notifier_unreg ; 
 int /*<<< orphan*/  devres_add (struct device*,struct extcon_dev_notifier_devres*) ; 
 struct extcon_dev_notifier_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct extcon_dev_notifier_devres*) ; 
 int extcon_register_notifier (struct extcon_dev*,unsigned int,struct notifier_block*) ; 

int devm_extcon_register_notifier(struct device *dev, struct extcon_dev *edev,
				unsigned int id, struct notifier_block *nb)
{
	struct extcon_dev_notifier_devres *ptr;
	int ret;

	ptr = devres_alloc(devm_extcon_dev_notifier_unreg, sizeof(*ptr),
				GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = extcon_register_notifier(edev, id, nb);
	if (ret) {
		devres_free(ptr);
		return ret;
	}

	ptr->edev = edev;
	ptr->id = id;
	ptr->nb = nb;
	devres_add(dev, ptr);

	return 0;
}