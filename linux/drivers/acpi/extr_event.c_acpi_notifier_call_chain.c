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
typedef  void* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bus_id; int /*<<< orphan*/  device_class; } ;
struct acpi_device {TYPE_1__ pnp; } ;
struct acpi_bus_event {void* data; void* type; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  device_class; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NOTIFY_BAD ; 
 int /*<<< orphan*/  acpi_chain_head ; 
 scalar_t__ blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int acpi_notifier_call_chain(struct acpi_device *dev, u32 type, u32 data)
{
	struct acpi_bus_event event;

	strcpy(event.device_class, dev->pnp.device_class);
	strcpy(event.bus_id, dev->pnp.bus_id);
	event.type = type;
	event.data = data;
	return (blocking_notifier_call_chain(&acpi_chain_head, 0, (void *)&event)
                        == NOTIFY_BAD) ? -EINVAL : 0;
}