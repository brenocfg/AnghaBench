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
struct sysc {int dummy; } ;
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 128 
 int NOTIFY_DONE ; 
 int sysc_child_add_clocks (struct sysc*,struct device*) ; 
 struct sysc* sysc_child_to_parent (struct device*) ; 
 int /*<<< orphan*/  sysc_legacy_idle_quirk (struct sysc*,struct device*) ; 

__attribute__((used)) static int sysc_notifier_call(struct notifier_block *nb,
			      unsigned long event, void *device)
{
	struct device *dev = device;
	struct sysc *ddata;
	int error;

	ddata = sysc_child_to_parent(dev);
	if (!ddata)
		return NOTIFY_DONE;

	switch (event) {
	case BUS_NOTIFY_ADD_DEVICE:
		error = sysc_child_add_clocks(ddata, dev);
		if (error)
			return error;
		sysc_legacy_idle_quirk(ddata, dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}