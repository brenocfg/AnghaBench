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
struct resource {int dummy; } ;
struct resource_win {struct resource res; } ;
struct acpi_resource {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_dev_resource_address_space (struct acpi_resource*,struct resource_win*) ; 
 scalar_t__ acpi_dev_resource_ext_address_space (struct acpi_resource*,struct resource_win*) ; 
 scalar_t__ acpi_dev_resource_memory (struct acpi_resource*,struct resource*) ; 
 int /*<<< orphan*/  memset (struct resource_win*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int is_memory(struct acpi_resource *ares, void *not_used)
{
	struct resource_win win;
	struct resource *res = &win.res;

	memset(&win, 0, sizeof(win));

	return !(acpi_dev_resource_memory(ares, res)
	       || acpi_dev_resource_address_space(ares, &win)
	       || acpi_dev_resource_ext_address_space(ares, &win));
}