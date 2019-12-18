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
struct vmbus_ic_desc {int /*<<< orphan*/ * ic_desc; int /*<<< orphan*/  ic_guid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ VMBUS_PROBE_GUID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_disabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vmbus_ic_probe(device_t dev, const struct vmbus_ic_desc descs[])
{
	device_t bus = device_get_parent(dev);
	const struct vmbus_ic_desc *d;

	if (resource_disabled(device_get_name(dev), 0))
		return (ENXIO);

	for (d = descs; d->ic_desc != NULL; ++d) {
		if (VMBUS_PROBE_GUID(bus, dev, &d->ic_guid) == 0) {
			device_set_desc(dev, d->ic_desc);
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}