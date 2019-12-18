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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct acpi_generic_address {int bit_offset; int bit_width; scalar_t__ space_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;
typedef  scalar_t__ acpi_io_address ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_DB_IO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_DIV_8 (int) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_BITS (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MASK_BITS_ABOVE_64 (int) ; 
 int acpi_hw_get_access_bit_width (scalar_t__,struct acpi_generic_address*,int) ; 
 int /*<<< orphan*/  acpi_hw_validate_register (struct acpi_generic_address*,int,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_hw_write_port (scalar_t__,int,int) ; 
 int /*<<< orphan*/  acpi_os_write_memory (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (scalar_t__) ; 
 int /*<<< orphan*/  hw_write ; 

acpi_status acpi_hw_write(u64 value, struct acpi_generic_address *reg)
{
	u64 address;
	u8 access_width;
	u32 bit_width;
	u8 bit_offset;
	u64 value64;
	u8 index;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_write);

	/* Validate contents of the GAS register */

	status = acpi_hw_validate_register(reg, 64, &address);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Convert access_width into number of bits based */

	access_width = acpi_hw_get_access_bit_width(address, reg, 64);
	bit_width = reg->bit_offset + reg->bit_width;
	bit_offset = reg->bit_offset;

	/*
	 * Two address spaces supported: Memory or IO. PCI_Config is
	 * not supported here because the GAS structure is insufficient
	 */
	index = 0;
	while (bit_width) {
		/*
		 * Use offset style bit reads because "Index * AccessWidth" is
		 * ensured to be less than 64-bits by acpi_hw_validate_register().
		 */
		value64 = ACPI_GET_BITS(&value, index * access_width,
					ACPI_MASK_BITS_ABOVE_64(access_width));

		if (bit_offset >= access_width) {
			bit_offset -= access_width;
		} else {
			if (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) {
				status =
				    acpi_os_write_memory((acpi_physical_address)
							 address +
							 index *
							 ACPI_DIV_8
							 (access_width),
							 value64, access_width);
			} else {	/* ACPI_ADR_SPACE_SYSTEM_IO, validated earlier */

				status = acpi_hw_write_port((acpi_io_address)
							    address +
							    index *
							    ACPI_DIV_8
							    (access_width),
							    (u32)value64,
							    access_width);
			}
		}

		/*
		 * Index * access_width is ensured to be less than 32-bits by
		 * acpi_hw_validate_register().
		 */
		bit_width -=
		    bit_width > access_width ? access_width : bit_width;
		index++;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "Wrote: %8.8X%8.8X width %2d   to %8.8X%8.8X (%s)\n",
			  ACPI_FORMAT_UINT64(value), access_width,
			  ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(reg->space_id)));

	return (status);
}