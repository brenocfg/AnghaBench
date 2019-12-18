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
typedef  int /*<<< orphan*/  u64 ;
struct acpi_generic_address {int space_id; int bit_width; scalar_t__ access_width; scalar_t__ bit_offset; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int ACPI_FADT_GPE_REGISTER ; 
 int /*<<< orphan*/  ACPI_MOVE_64_TO_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_INFO ; 

__attribute__((used)) static void
acpi_tb_init_generic_address(struct acpi_generic_address *generic_address,
			     u8 space_id,
			     u8 byte_width,
			     u64 address, const char *register_name, u8 flags)
{
	u8 bit_width;

	/*
	 * Bit width field in the GAS is only one byte long, 255 max.
	 * Check for bit_width overflow in GAS.
	 */
	bit_width = (u8)(byte_width * 8);
	if (byte_width > 31) {	/* (31*8)=248, (32*8)=256 */
		/*
		 * No error for GPE blocks, because we do not use the bit_width
		 * for GPEs, the legacy length (byte_width) is used instead to
		 * allow for a large number of GPEs.
		 */
		if (!(flags & ACPI_FADT_GPE_REGISTER)) {
			ACPI_ERROR((AE_INFO,
				    "%s - 32-bit FADT register is too long (%u bytes, %u bits) "
				    "to convert to GAS struct - 255 bits max, truncating",
				    register_name, byte_width,
				    (byte_width * 8)));
		}

		bit_width = 255;
	}

	/*
	 * The 64-bit Address field is non-aligned in the byte packed
	 * GAS struct.
	 */
	ACPI_MOVE_64_TO_64(&generic_address->address, &address);

	/* All other fields are byte-wide */

	generic_address->space_id = space_id;
	generic_address->bit_width = bit_width;
	generic_address->bit_offset = 0;
	generic_address->access_width = 0;	/* Access width ANY */
}