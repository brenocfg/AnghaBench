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
struct acpi_ec {int /*<<< orphan*/  flags; int /*<<< orphan*/  gpe; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_FLAGS_EC_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  EC_FLAGS_EVT_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  EC_FLAGS_GPE_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  acpi_ec_gpe_handler ; 
 int /*<<< orphan*/  acpi_ec_remove_query_handlers (struct acpi_ec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_space_handler ; 
 int /*<<< orphan*/  acpi_ec_stop (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_gpe_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ec_remove_handlers(struct acpi_ec *ec)
{
	if (test_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags)) {
		if (ACPI_FAILURE(acpi_remove_address_space_handler(ec->handle,
					ACPI_ADR_SPACE_EC, &acpi_ec_space_handler)))
			pr_err("failed to remove space handler\n");
		clear_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags);
	}

	/*
	 * Stops handling the EC transactions after removing the operation
	 * region handler. This is required because _REG(DISCONNECT)
	 * invoked during the removal can result in new EC transactions.
	 *
	 * Flushes the EC requests and thus disables the GPE before
	 * removing the GPE handler. This is required by the current ACPICA
	 * GPE core. ACPICA GPE core will automatically disable a GPE when
	 * it is indicated but there is no way to handle it. So the drivers
	 * must disable the GPEs prior to removing the GPE handlers.
	 */
	acpi_ec_stop(ec, false);

	if (test_bit(EC_FLAGS_GPE_HANDLER_INSTALLED, &ec->flags)) {
		if (ACPI_FAILURE(acpi_remove_gpe_handler(NULL, ec->gpe,
					&acpi_ec_gpe_handler)))
			pr_err("failed to remove gpe handler\n");
		clear_bit(EC_FLAGS_GPE_HANDLER_INSTALLED, &ec->flags);
	}
	if (test_bit(EC_FLAGS_EVT_HANDLER_INSTALLED, &ec->flags)) {
		acpi_ec_remove_query_handlers(ec, true, 0);
		clear_bit(EC_FLAGS_EVT_HANDLER_INSTALLED, &ec->flags);
	}
}