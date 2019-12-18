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
typedef  int u64 ;
typedef  int u32 ;
struct acpi_mem_space_context {scalar_t__ mapped_physical_address; int mapped_length; scalar_t__ address; scalar_t__ length; void* mapped_logical_address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;
typedef  scalar_t__ acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DEFAULT_PAGE_SIZE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET16 (void*) ; 
 scalar_t__ ACPI_GET32 (void*) ; 
 scalar_t__ ACPI_GET64 (void*) ; 
 scalar_t__ ACPI_GET8 (void*) ; 
#define  ACPI_READ 129 
 scalar_t__ ACPI_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_SET16 (void*,int) ; 
 int /*<<< orphan*/  ACPI_SET32 (void*,int) ; 
 int /*<<< orphan*/  ACPI_SET64 (void*,int) ; 
 int /*<<< orphan*/  ACPI_SET8 (void*,int) ; 
#define  ACPI_WRITE 128 
 int /*<<< orphan*/  AE_AML_ALIGNMENT ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 void* acpi_os_map_memory (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (void*,int) ; 
 int /*<<< orphan*/  acpi_ut_short_divide (int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ex_system_memory_space_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_system_memory_space_handler(u32 function,
				    acpi_physical_address address,
				    u32 bit_width,
				    u64 *value,
				    void *handler_context, void *region_context)
{
	acpi_status status = AE_OK;
	void *logical_addr_ptr = NULL;
	struct acpi_mem_space_context *mem_info = region_context;
	u32 length;
	acpi_size map_length;
	acpi_size page_boundary_map_length;
#ifdef ACPI_MISALIGNMENT_NOT_SUPPORTED
	u32 remainder;
#endif

	ACPI_FUNCTION_TRACE(ex_system_memory_space_handler);

	/* Validate and translate the bit width */

	switch (bit_width) {
	case 8:

		length = 1;
		break;

	case 16:

		length = 2;
		break;

	case 32:

		length = 4;
		break;

	case 64:

		length = 8;
		break;

	default:

		ACPI_ERROR((AE_INFO, "Invalid SystemMemory width %u",
			    bit_width));
		return_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	}

#ifdef ACPI_MISALIGNMENT_NOT_SUPPORTED
	/*
	 * Hardware does not support non-aligned data transfers, we must verify
	 * the request.
	 */
	(void)acpi_ut_short_divide((u64) address, length, NULL, &remainder);
	if (remainder != 0) {
		return_ACPI_STATUS(AE_AML_ALIGNMENT);
	}
#endif

	/*
	 * Does the request fit into the cached memory mapping?
	 * Is 1) Address below the current mapping? OR
	 *    2) Address beyond the current mapping?
	 */
	if ((address < mem_info->mapped_physical_address) ||
	    (((u64) address + length) > ((u64)
					 mem_info->mapped_physical_address +
					 mem_info->mapped_length))) {
		/*
		 * The request cannot be resolved by the current memory mapping;
		 * Delete the existing mapping and create a new one.
		 */
		if (mem_info->mapped_length) {

			/* Valid mapping, delete it */

			acpi_os_unmap_memory(mem_info->mapped_logical_address,
					     mem_info->mapped_length);
		}

		/*
		 * October 2009: Attempt to map from the requested address to the
		 * end of the region. However, we will never map more than one
		 * page, nor will we cross a page boundary.
		 */
		map_length = (acpi_size)
		    ((mem_info->address + mem_info->length) - address);

		/*
		 * If mapping the entire remaining portion of the region will cross
		 * a page boundary, just map up to the page boundary, do not cross.
		 * On some systems, crossing a page boundary while mapping regions
		 * can cause warnings if the pages have different attributes
		 * due to resource management.
		 *
		 * This has the added benefit of constraining a single mapping to
		 * one page, which is similar to the original code that used a 4k
		 * maximum window.
		 */
		page_boundary_map_length = (acpi_size)
		    (ACPI_ROUND_UP(address, ACPI_DEFAULT_PAGE_SIZE) - address);
		if (page_boundary_map_length == 0) {
			page_boundary_map_length = ACPI_DEFAULT_PAGE_SIZE;
		}

		if (map_length > page_boundary_map_length) {
			map_length = page_boundary_map_length;
		}

		/* Create a new mapping starting at the address given */

		mem_info->mapped_logical_address =
		    acpi_os_map_memory(address, map_length);
		if (!mem_info->mapped_logical_address) {
			ACPI_ERROR((AE_INFO,
				    "Could not map memory at 0x%8.8X%8.8X, size %u",
				    ACPI_FORMAT_UINT64(address),
				    (u32)map_length));
			mem_info->mapped_length = 0;
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/* Save the physical address and mapping size */

		mem_info->mapped_physical_address = address;
		mem_info->mapped_length = map_length;
	}

	/*
	 * Generate a logical pointer corresponding to the address we want to
	 * access
	 */
	logical_addr_ptr = mem_info->mapped_logical_address +
	    ((u64) address - (u64) mem_info->mapped_physical_address);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "System-Memory (width %u) R/W %u Address=%8.8X%8.8X\n",
			  bit_width, function, ACPI_FORMAT_UINT64(address)));

	/*
	 * Perform the memory read or write
	 *
	 * Note: For machines that do not support non-aligned transfers, the target
	 * address was checked for alignment above. We do not attempt to break the
	 * transfer up into smaller (byte-size) chunks because the AML specifically
	 * asked for a transfer width that the hardware may require.
	 */
	switch (function) {
	case ACPI_READ:

		*value = 0;
		switch (bit_width) {
		case 8:

			*value = (u64)ACPI_GET8(logical_addr_ptr);
			break;

		case 16:

			*value = (u64)ACPI_GET16(logical_addr_ptr);
			break;

		case 32:

			*value = (u64)ACPI_GET32(logical_addr_ptr);
			break;

		case 64:

			*value = (u64)ACPI_GET64(logical_addr_ptr);
			break;

		default:

			/* bit_width was already validated */

			break;
		}
		break;

	case ACPI_WRITE:

		switch (bit_width) {
		case 8:

			ACPI_SET8(logical_addr_ptr, *value);
			break;

		case 16:

			ACPI_SET16(logical_addr_ptr, *value);
			break;

		case 32:

			ACPI_SET32(logical_addr_ptr, *value);
			break;

		case 64:

			ACPI_SET64(logical_addr_ptr, *value);
			break;

		default:

			/* bit_width was already validated */

			break;
		}
		break;

	default:

		status = AE_BAD_PARAMETER;
		break;
	}

	return_ACPI_STATUS(status);
}