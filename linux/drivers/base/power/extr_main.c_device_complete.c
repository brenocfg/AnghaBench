#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ syscore; } ;
struct device {TYPE_11__* driver; TYPE_9__* bus; TYPE_7__* class; TYPE_5__* type; TYPE_3__* pm_domain; TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_22__ {TYPE_8__* pm; } ;
struct TYPE_21__ {void (* complete ) (struct device*) ;} ;
struct TYPE_20__ {TYPE_6__* pm; } ;
struct TYPE_19__ {void (* complete ) (struct device*) ;} ;
struct TYPE_18__ {TYPE_4__* pm; } ;
struct TYPE_17__ {void (* complete ) (struct device*) ;} ;
struct TYPE_15__ {void (* complete ) (struct device*) ;} ;
struct TYPE_16__ {TYPE_2__ ops; } ;
struct TYPE_13__ {TYPE_10__* pm; } ;
struct TYPE_12__ {void (* complete ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  pm_dev_dbg (struct device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

__attribute__((used)) static void device_complete(struct device *dev, pm_message_t state)
{
	void (*callback)(struct device *) = NULL;
	const char *info = NULL;

	if (dev->power.syscore)
		return;

	device_lock(dev);

	if (dev->pm_domain) {
		info = "completing power domain ";
		callback = dev->pm_domain->ops.complete;
	} else if (dev->type && dev->type->pm) {
		info = "completing type ";
		callback = dev->type->pm->complete;
	} else if (dev->class && dev->class->pm) {
		info = "completing class ";
		callback = dev->class->pm->complete;
	} else if (dev->bus && dev->bus->pm) {
		info = "completing bus ";
		callback = dev->bus->pm->complete;
	}

	if (!callback && dev->driver && dev->driver->pm) {
		info = "completing driver ";
		callback = dev->driver->pm->complete;
	}

	if (callback) {
		pm_dev_dbg(dev, state, info);
		callback(dev);
	}

	device_unlock(dev);

	pm_runtime_put(dev);
}