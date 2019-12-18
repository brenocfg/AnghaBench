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
typedef  size_t u32 ;
typedef  int acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEFAULT_HANDLER ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 size_t ACPI_NUM_DEFAULT_SPACES ; 
#define  AE_ALREADY_EXISTS 130 
#define  AE_OK 129 
#define  AE_SAME_HANDLER 128 
 int acpi_ev_install_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acpi_gbl_default_address_spaces ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_install_region_handlers ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int) ; 

acpi_status acpi_ev_install_region_handlers(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ev_install_region_handlers);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * All address spaces (PCI Config, EC, SMBus) are scope dependent and
	 * registration must occur for a specific device.
	 *
	 * In the case of the system memory and IO address spaces there is
	 * currently no device associated with the address space. For these we
	 * use the root.
	 *
	 * We install the default PCI config space handler at the root so that
	 * this space is immediately available even though the we have not
	 * enumerated all the PCI Root Buses yet. This is to conform to the ACPI
	 * specification which states that the PCI config space must be always
	 * available -- even though we are nowhere near ready to find the PCI root
	 * buses at this point.
	 *
	 * NOTE: We ignore AE_ALREADY_EXISTS because this means that a handler
	 * has already been installed (via acpi_install_address_space_handler).
	 * Similar for AE_SAME_HANDLER.
	 */
	for (i = 0; i < ACPI_NUM_DEFAULT_SPACES; i++) {
		status = acpi_ev_install_space_handler(acpi_gbl_root_node,
						       acpi_gbl_default_address_spaces
						       [i],
						       ACPI_DEFAULT_HANDLER,
						       NULL, NULL);
		switch (status) {
		case AE_OK:
		case AE_SAME_HANDLER:
		case AE_ALREADY_EXISTS:

			/* These exceptions are all OK */

			status = AE_OK;
			break;

		default:

			goto unlock_and_exit;
		}
	}

unlock_and_exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return_ACPI_STATUS(status);
}