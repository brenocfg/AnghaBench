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
struct TYPE_3__ {scalar_t__ flags; } ;
struct resource_win {TYPE_1__ res; } ;
struct acpi_resource_extended_address64 {int /*<<< orphan*/  address; } ;
struct acpi_resource_address {int dummy; } ;
struct TYPE_4__ {struct acpi_resource_extended_address64 ext_address64; } ;
struct acpi_resource {scalar_t__ type; TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 ; 
 int acpi_decode_space (struct resource_win*,struct acpi_resource_address*,int /*<<< orphan*/ *) ; 

bool acpi_dev_resource_ext_address_space(struct acpi_resource *ares,
					 struct resource_win *win)
{
	struct acpi_resource_extended_address64 *ext_addr;

	win->res.flags = 0;
	if (ares->type != ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64)
		return false;

	ext_addr = &ares->data.ext_address64;

	return acpi_decode_space(win, (struct acpi_resource_address *)ext_addr,
				 &ext_addr->address);
}