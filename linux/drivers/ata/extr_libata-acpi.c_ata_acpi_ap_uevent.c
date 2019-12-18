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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_device {int /*<<< orphan*/  hp; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ ata_hotplug_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_acpi_ap_uevent(struct acpi_device *adev, u32 event)
{
	ata_acpi_uevent(ata_hotplug_data(adev->hp).ap, NULL, event);
}