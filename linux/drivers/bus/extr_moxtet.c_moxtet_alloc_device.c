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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct moxtet_device {TYPE_1__ dev; struct moxtet* moxtet; } ;
struct moxtet {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 struct moxtet_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moxtet_bus_type ; 
 int /*<<< orphan*/  moxtet_dev_release ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct moxtet_device *
moxtet_alloc_device(struct moxtet *moxtet)
{
	struct moxtet_device *dev;

	if (!get_device(moxtet->dev))
		return NULL;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		put_device(moxtet->dev);
		return NULL;
	}

	dev->moxtet = moxtet;
	dev->dev.parent = moxtet->dev;
	dev->dev.bus = &moxtet_bus_type;
	dev->dev.release = moxtet_dev_release;

	device_initialize(&dev->dev);

	return dev;
}