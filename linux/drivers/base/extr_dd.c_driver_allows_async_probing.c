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
struct device_driver {int probe_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  PROBE_FORCE_SYNCHRONOUS 129 
#define  PROBE_PREFER_ASYNCHRONOUS 128 
 int /*<<< orphan*/  cmdline_requested_async_probing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_requested_async_probing (int /*<<< orphan*/ ) ; 

bool driver_allows_async_probing(struct device_driver *drv)
{
	switch (drv->probe_type) {
	case PROBE_PREFER_ASYNCHRONOUS:
		return true;

	case PROBE_FORCE_SYNCHRONOUS:
		return false;

	default:
		if (cmdline_requested_async_probing(drv->name))
			return true;

		if (module_requested_async_probing(drv->owner))
			return true;

		return false;
	}
}