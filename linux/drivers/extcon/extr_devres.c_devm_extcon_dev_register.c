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
struct extcon_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_extcon_dev_unreg ; 
 int /*<<< orphan*/  devres_add (struct device*,struct extcon_dev**) ; 
 struct extcon_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct extcon_dev**) ; 
 int extcon_dev_register (struct extcon_dev*) ; 

int devm_extcon_dev_register(struct device *dev, struct extcon_dev *edev)
{
	struct extcon_dev **ptr;
	int ret;

	ptr = devres_alloc(devm_extcon_dev_unreg, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = extcon_dev_register(edev);
	if (ret) {
		devres_free(ptr);
		return ret;
	}

	*ptr = edev;
	devres_add(dev, ptr);

	return 0;
}