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
struct TYPE_9__ {int /*<<< orphan*/  power_resources; } ;
struct TYPE_10__ {TYPE_1__* states; TYPE_4__ flags; } ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_8__ {int /*<<< orphan*/  resources; TYPE_2__ flags; } ;
struct acpi_device {TYPE_5__ power; TYPE_3__ wakeup; } ;
struct TYPE_6__ {int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_D3_HOT ; 
 int /*<<< orphan*/  acpi_power_expose_hide (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * attr_groups ; 
 int /*<<< orphan*/  wakeup_attr_group ; 

void acpi_power_add_remove_device(struct acpi_device *adev, bool add)
{
	int state;

	if (adev->wakeup.flags.valid)
		acpi_power_expose_hide(adev, &adev->wakeup.resources,
				       &wakeup_attr_group, add);

	if (!adev->power.flags.power_resources)
		return;

	for (state = ACPI_STATE_D0; state <= ACPI_STATE_D3_HOT; state++)
		acpi_power_expose_hide(adev,
				       &adev->power.states[state].resources,
				       &attr_groups[state], add);
}