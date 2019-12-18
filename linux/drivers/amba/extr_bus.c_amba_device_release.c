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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct amba_device {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct amba_device*) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 struct amba_device* to_amba_device (struct device*) ; 

__attribute__((used)) static void amba_device_release(struct device *dev)
{
	struct amba_device *d = to_amba_device(dev);

	if (d->res.parent)
		release_resource(&d->res);
	kfree(d);
}