#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_4__* bus; TYPE_3__* class; TYPE_2__* type; TYPE_1__* pm_domain; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  int /*<<< orphan*/ * pm_callback_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_5__ {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pm_late_early_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pm_callback_t dpm_subsys_suspend_late_cb(struct device *dev,
						pm_message_t state,
						const char **info_p)
{
	pm_callback_t callback;
	const char *info;

	if (dev->pm_domain) {
		info = "late power domain ";
		callback = pm_late_early_op(&dev->pm_domain->ops, state);
	} else if (dev->type && dev->type->pm) {
		info = "late type ";
		callback = pm_late_early_op(dev->type->pm, state);
	} else if (dev->class && dev->class->pm) {
		info = "late class ";
		callback = pm_late_early_op(dev->class->pm, state);
	} else if (dev->bus && dev->bus->pm) {
		info = "late bus ";
		callback = pm_late_early_op(dev->bus->pm, state);
	} else {
		return NULL;
	}

	if (info_p)
		*info_p = info;

	return callback;
}