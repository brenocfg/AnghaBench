#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_5__* driver; TYPE_4__* bus; TYPE_3__* class; TYPE_2__* type; TYPE_1__* pm_domain; } ;
struct dev_pm_ops {int dummy; } ;
typedef  int /*<<< orphan*/ * pm_callback_t ;
struct TYPE_10__ {scalar_t__ pm; } ;
struct TYPE_9__ {struct dev_pm_ops* pm; } ;
struct TYPE_8__ {struct dev_pm_ops* pm; } ;
struct TYPE_7__ {struct dev_pm_ops* pm; } ;
struct TYPE_6__ {struct dev_pm_ops ops; } ;

/* Variables and functions */

__attribute__((used)) static pm_callback_t __rpm_get_callback(struct device *dev, size_t cb_offset)
{
	pm_callback_t cb;
	const struct dev_pm_ops *ops;

	if (dev->pm_domain)
		ops = &dev->pm_domain->ops;
	else if (dev->type && dev->type->pm)
		ops = dev->type->pm;
	else if (dev->class && dev->class->pm)
		ops = dev->class->pm;
	else if (dev->bus && dev->bus->pm)
		ops = dev->bus->pm;
	else
		ops = NULL;

	if (ops)
		cb = *(pm_callback_t *)((void *)ops + cb_offset);
	else
		cb = NULL;

	if (!cb && dev->driver && dev->driver->pm)
		cb = *(pm_callback_t *)((void *)dev->driver->pm + cb_offset);

	return cb;
}