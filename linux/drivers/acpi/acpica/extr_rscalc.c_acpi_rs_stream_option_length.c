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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (scalar_t__) ; 

__attribute__((used)) static u32
acpi_rs_stream_option_length(u32 resource_length,
			     u32 minimum_aml_resource_length)
{
	u32 string_length = 0;

	ACPI_FUNCTION_ENTRY();

	/*
	 * The resource_source_index and resource_source are optional elements of
	 * some Large-type resource descriptors.
	 */

	/*
	 * If the length of the actual resource descriptor is greater than the
	 * ACPI spec-defined minimum length, it means that a resource_source_index
	 * exists and is followed by a (required) null terminated string. The
	 * string length (including the null terminator) is the resource length
	 * minus the minimum length, minus one byte for the resource_source_index
	 * itself.
	 */
	if (resource_length > minimum_aml_resource_length) {

		/* Compute the length of the optional string */

		string_length =
		    resource_length - minimum_aml_resource_length - 1;
	}

	/*
	 * Round the length up to a multiple of the native word in order to
	 * guarantee that the entire resource descriptor is native word aligned
	 */
	return ((u32) ACPI_ROUND_UP_TO_NATIVE_WORD(string_length));
}