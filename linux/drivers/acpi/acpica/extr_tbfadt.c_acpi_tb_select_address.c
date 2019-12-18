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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ acpi_gbl_use32_bit_fadt_addresses ; 

__attribute__((used)) static u64
acpi_tb_select_address(char *register_name, u32 address32, u64 address64)
{

	if (!address64) {

		/* 64-bit address is zero, use 32-bit address */

		return ((u64)address32);
	}

	if (address32 && (address64 != (u64)address32)) {

		/* Address mismatch between 32-bit and 64-bit versions */

		ACPI_BIOS_WARNING((AE_INFO,
				   "32/64X %s address mismatch in FADT: "
				   "0x%8.8X/0x%8.8X%8.8X, using %u-bit address",
				   register_name, address32,
				   ACPI_FORMAT_UINT64(address64),
				   acpi_gbl_use32_bit_fadt_addresses ? 32 :
				   64));

		/* 32-bit address override */

		if (acpi_gbl_use32_bit_fadt_addresses) {
			return ((u64)address32);
		}
	}

	/* Default is to use the 64-bit address */

	return (address64);
}