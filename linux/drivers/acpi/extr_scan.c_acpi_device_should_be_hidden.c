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
struct resource {scalar_t__ start; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_get_resource_memory ; 
 int /*<<< orphan*/  acpi_handle_info (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ spcr_uart_addr ; 

__attribute__((used)) static bool acpi_device_should_be_hidden(acpi_handle handle)
{
	acpi_status status;
	struct resource res;

	/* Check if it should ignore the UART device */
	if (!(spcr_uart_addr && acpi_has_method(handle, METHOD_NAME__CRS)))
		return false;

	/*
	 * The UART device described in SPCR table is assumed to have only one
	 * memory resource present. So we only look for the first one here.
	 */
	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     acpi_get_resource_memory, &res);
	if (ACPI_FAILURE(status) || res.start != spcr_uart_addr)
		return false;

	acpi_handle_info(handle, "The UART device @%pa in SPCR table will be hidden\n",
			 &res.start);

	return true;
}