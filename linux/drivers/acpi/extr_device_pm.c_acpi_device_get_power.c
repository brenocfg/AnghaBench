#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bus_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  ignore_parent; scalar_t__ explicit_get; scalar_t__ power_resources; } ;
struct TYPE_9__ {TYPE_2__ flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  power_manageable; } ;
struct acpi_device {TYPE_6__ pnp; TYPE_5__* parent; TYPE_3__ power; TYPE_1__ flags; } ;
struct TYPE_10__ {int state; } ;
struct TYPE_11__ {TYPE_4__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D2 ; 
 int ACPI_STATE_D3_COLD ; 
 int ACPI_STATE_D3_HOT ; 
 int ACPI_STATE_UNKNOWN ; 
 int EINVAL ; 
 int acpi_dev_pm_explicit_get (struct acpi_device*,int*) ; 
 int acpi_power_get_inferred_state (struct acpi_device*,int*) ; 
 int /*<<< orphan*/  acpi_power_state_string (int) ; 

int acpi_device_get_power(struct acpi_device *device, int *state)
{
	int result = ACPI_STATE_UNKNOWN;
	int error;

	if (!device || !state)
		return -EINVAL;

	if (!device->flags.power_manageable) {
		/* TBD: Non-recursive algorithm for walking up hierarchy. */
		*state = device->parent ?
			device->parent->power.state : ACPI_STATE_D0;
		goto out;
	}

	/*
	 * Get the device's power state from power resources settings and _PSC,
	 * if available.
	 */
	if (device->power.flags.power_resources) {
		error = acpi_power_get_inferred_state(device, &result);
		if (error)
			return error;
	}
	if (device->power.flags.explicit_get) {
		int psc;

		error = acpi_dev_pm_explicit_get(device, &psc);
		if (error)
			return error;

		/*
		 * The power resources settings may indicate a power state
		 * shallower than the actual power state of the device, because
		 * the same power resources may be referenced by other devices.
		 *
		 * For systems predating ACPI 4.0 we assume that D3hot is the
		 * deepest state that can be supported.
		 */
		if (psc > result && psc < ACPI_STATE_D3_COLD)
			result = psc;
		else if (result == ACPI_STATE_UNKNOWN)
			result = psc > ACPI_STATE_D2 ? ACPI_STATE_D3_HOT : psc;
	}

	/*
	 * If we were unsure about the device parent's power state up to this
	 * point, the fact that the device is in D0 implies that the parent has
	 * to be in D0 too, except if ignore_parent is set.
	 */
	if (!device->power.flags.ignore_parent && device->parent
	    && device->parent->power.state == ACPI_STATE_UNKNOWN
	    && result == ACPI_STATE_D0)
		device->parent->power.state = ACPI_STATE_D0;

	*state = result;

 out:
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Device [%s] power state is %s\n",
			  device->pnp.bus_id, acpi_power_state_string(*state)));

	return 0;
}