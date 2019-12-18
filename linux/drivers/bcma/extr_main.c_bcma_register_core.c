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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct bcma_device {int dev_registered; int /*<<< orphan*/  dev; TYPE_1__ id; } ;
struct bcma_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,int /*<<< orphan*/ ) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcma_register_core(struct bcma_bus *bus, struct bcma_device *core)
{
	int err;

	err = device_register(&core->dev);
	if (err) {
		bcma_err(bus, "Could not register dev for core 0x%03X\n",
			 core->id.id);
		put_device(&core->dev);
		return;
	}
	core->dev_registered = true;
}