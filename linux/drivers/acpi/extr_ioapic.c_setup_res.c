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
typedef  int /*<<< orphan*/  win ;
struct resource {int flags; } ;
struct resource_win {struct resource res; } ;
struct acpi_resource {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IORESOURCE_PREFETCH ; 
 scalar_t__ acpi_dev_filter_resource_type (struct acpi_resource*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_dev_resource_address_space (struct acpi_resource*,struct resource_win*) ; 
 scalar_t__ acpi_dev_resource_ext_address_space (struct acpi_resource*,struct resource_win*) ; 
 int /*<<< orphan*/  acpi_dev_resource_memory (struct acpi_resource*,struct resource*) ; 
 int /*<<< orphan*/  memset (struct resource_win*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static acpi_status setup_res(struct acpi_resource *acpi_res, void *data)
{
	struct resource *res = data;
	struct resource_win win;

	/*
	 * We might assign this to 'res' later, make sure all pointers are
	 * cleared before the resource is added to the global list
	 */
	memset(&win, 0, sizeof(win));

	res->flags = 0;
	if (acpi_dev_filter_resource_type(acpi_res, IORESOURCE_MEM))
		return AE_OK;

	if (!acpi_dev_resource_memory(acpi_res, res)) {
		if (acpi_dev_resource_address_space(acpi_res, &win) ||
		    acpi_dev_resource_ext_address_space(acpi_res, &win))
			*res = win.res;
	}
	if ((res->flags & IORESOURCE_PREFETCH) ||
	    (res->flags & IORESOURCE_DISABLED))
		res->flags = 0;

	return AE_CTRL_TERMINATE;
}