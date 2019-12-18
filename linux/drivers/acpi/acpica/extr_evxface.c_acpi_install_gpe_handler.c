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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
typedef  int /*<<< orphan*/  acpi_gpe_handler ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_ev_install_gpe_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_install_gpe_handler(acpi_handle gpe_device,
			 u32 gpe_number,
			 u32 type, acpi_gpe_handler address, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_gpe_handler);

	status = acpi_ev_install_gpe_handler(gpe_device, gpe_number, type,
					     FALSE, address, context);

	return_ACPI_STATUS(status);
}