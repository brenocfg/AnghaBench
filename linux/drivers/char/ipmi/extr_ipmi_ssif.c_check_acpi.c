#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ acpi_handle; } ;
struct TYPE_4__ {TYPE_1__ acpi_info; } ;
struct ssif_info {TYPE_2__ addr_info; int /*<<< orphan*/  addr_source; } ;
struct device {int dummy; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  SI_ACPI ; 

__attribute__((used)) static bool check_acpi(struct ssif_info *ssif_info, struct device *dev)
{
#ifdef CONFIG_ACPI
	acpi_handle acpi_handle;

	acpi_handle = ACPI_HANDLE(dev);
	if (acpi_handle) {
		ssif_info->addr_source = SI_ACPI;
		ssif_info->addr_info.acpi_info.acpi_handle = acpi_handle;
		return true;
	}
#endif
	return false;
}