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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct acpi_generic_address {scalar_t__ space_id; int access_width; scalar_t__ bit_width; scalar_t__ bit_offset; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_64_TO_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_ADDRESS ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 scalar_t__ acpi_hw_get_access_bit_width (int /*<<< orphan*/ ,struct acpi_generic_address*,scalar_t__) ; 

acpi_status
acpi_hw_validate_register(struct acpi_generic_address *reg,
			  u8 max_bit_width, u64 *address)
{
	u8 bit_width;
	u8 access_width;

	/* Must have a valid pointer to a GAS structure */

	if (!reg) {
		return (AE_BAD_PARAMETER);
	}

	/*
	 * Copy the target address. This handles possible alignment issues.
	 * Address must not be null. A null address also indicates an optional
	 * ACPI register that is not supported, so no error message.
	 */
	ACPI_MOVE_64_TO_64(address, &reg->address);
	if (!(*address)) {
		return (AE_BAD_ADDRESS);
	}

	/* Validate the space_ID */

	if ((reg->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (reg->space_id != ACPI_ADR_SPACE_SYSTEM_IO)) {
		ACPI_ERROR((AE_INFO,
			    "Unsupported address space: 0x%X", reg->space_id));
		return (AE_SUPPORT);
	}

	/* Validate the access_width */

	if (reg->access_width > 4) {
		ACPI_ERROR((AE_INFO,
			    "Unsupported register access width: 0x%X",
			    reg->access_width));
		return (AE_SUPPORT);
	}

	/* Validate the bit_width, convert access_width into number of bits */

	access_width =
	    acpi_hw_get_access_bit_width(*address, reg, max_bit_width);
	bit_width =
	    ACPI_ROUND_UP(reg->bit_offset + reg->bit_width, access_width);
	if (max_bit_width < bit_width) {
		ACPI_WARNING((AE_INFO,
			      "Requested bit width 0x%X is smaller than register bit width 0x%X",
			      max_bit_width, bit_width));
		return (AE_SUPPORT);
	}

	return (AE_OK);
}