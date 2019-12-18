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
typedef  size_t u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct moxtet_device {size_t idx; TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct moxtet {int /*<<< orphan*/  dev; int /*<<< orphan*/ * modules; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct moxtet_device* ERR_PTR (int) ; 
 size_t TURRIS_MOX_MAX_MODULES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*,...) ; 
 int moxtet_add_device (struct moxtet_device*) ; 
 struct moxtet_device* moxtet_alloc_device (struct moxtet*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static struct moxtet_device *
of_register_moxtet_device(struct moxtet *moxtet, struct device_node *nc)
{
	struct moxtet_device *dev;
	u32 val;
	int ret;

	dev = moxtet_alloc_device(moxtet);
	if (!dev) {
		dev_err(moxtet->dev,
			"Moxtet device alloc error for %pOF\n", nc);
		return ERR_PTR(-ENOMEM);
	}

	ret = of_property_read_u32(nc, "reg", &val);
	if (ret) {
		dev_err(moxtet->dev, "%pOF has no valid 'reg' property (%d)\n",
			nc, ret);
		goto err_put;
	}

	dev->idx = val;

	if (dev->idx >= TURRIS_MOX_MAX_MODULES) {
		dev_err(moxtet->dev, "%pOF Moxtet address 0x%x out of range\n",
			nc, dev->idx);
		ret = -EINVAL;
		goto err_put;
	}

	dev->id = moxtet->modules[dev->idx];

	if (!dev->id) {
		dev_err(moxtet->dev, "%pOF Moxtet address 0x%x is empty\n", nc,
			dev->idx);
		ret = -ENODEV;
		goto err_put;
	}

	of_node_get(nc);
	dev->dev.of_node = nc;

	ret = moxtet_add_device(dev);
	if (ret) {
		dev_err(moxtet->dev,
			"Moxtet device register error for %pOF\n", nc);
		of_node_put(nc);
		goto err_put;
	}

	return dev;

err_put:
	put_device(&dev->dev);
	return ERR_PTR(ret);
}