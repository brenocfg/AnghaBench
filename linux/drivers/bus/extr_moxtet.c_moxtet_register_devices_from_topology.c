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
struct moxtet_device {int idx; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct moxtet {int count; int /*<<< orphan*/  dev; int /*<<< orphan*/ * modules; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int moxtet_add_device (struct moxtet_device*) ; 
 struct moxtet_device* moxtet_alloc_device (struct moxtet*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
moxtet_register_devices_from_topology(struct moxtet *moxtet)
{
	struct moxtet_device *dev;
	int i, ret;

	for (i = 0; i < moxtet->count; ++i) {
		dev = moxtet_alloc_device(moxtet);
		if (!dev) {
			dev_err(moxtet->dev, "Moxtet device %u alloc error\n",
				i);
			continue;
		}

		dev->idx = i;
		dev->id = moxtet->modules[i];

		ret = moxtet_add_device(dev);
		if (ret && ret != -EBUSY) {
			put_device(&dev->dev);
			dev_err(moxtet->dev,
				"Moxtet device %u register error: %i\n", i,
				ret);
		}
	}
}