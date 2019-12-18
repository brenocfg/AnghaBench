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
typedef  int u32 ;

/* Variables and functions */
 char* ACPI_ALLOCATE (int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_NAMESEG_SIZE ; 
 int ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AML_DUAL_NAME_PREFIX ; 
 int /*<<< orphan*/  AML_MULTI_NAME_PREFIX ; 
 int /*<<< orphan*/  AML_PARENT_PREFIX ; 
 int /*<<< orphan*/  AML_ROOT_PREFIX ; 
 int /*<<< orphan*/  ex_allocate_name_string ; 
 int /*<<< orphan*/  return_PTR (char*) ; 

__attribute__((used)) static char *acpi_ex_allocate_name_string(u32 prefix_count, u32 num_name_segs)
{
	char *temp_ptr;
	char *name_string;
	u32 size_needed;

	ACPI_FUNCTION_TRACE(ex_allocate_name_string);

	/*
	 * Allow room for all \ and ^ prefixes, all segments and a multi_name_prefix.
	 * Also, one byte for the null terminator.
	 * This may actually be somewhat longer than needed.
	 */
	if (prefix_count == ACPI_UINT32_MAX) {

		/* Special case for root */

		size_needed = 1 + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	} else {
		size_needed =
		    prefix_count + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	}

	/*
	 * Allocate a buffer for the name.
	 * This buffer must be deleted by the caller!
	 */
	name_string = ACPI_ALLOCATE(size_needed);
	if (!name_string) {
		ACPI_ERROR((AE_INFO,
			    "Could not allocate size %u", size_needed));
		return_PTR(NULL);
	}

	temp_ptr = name_string;

	/* Set up Root or Parent prefixes if needed */

	if (prefix_count == ACPI_UINT32_MAX) {
		*temp_ptr++ = AML_ROOT_PREFIX;
	} else {
		while (prefix_count--) {
			*temp_ptr++ = AML_PARENT_PREFIX;
		}
	}

	/* Set up Dual or Multi prefixes if needed */

	if (num_name_segs > 2) {

		/* Set up multi prefixes   */

		*temp_ptr++ = AML_MULTI_NAME_PREFIX;
		*temp_ptr++ = (char)num_name_segs;
	} else if (2 == num_name_segs) {

		/* Set up dual prefixes */

		*temp_ptr++ = AML_DUAL_NAME_PREFIX;
	}

	/*
	 * Terminate string following prefixes. acpi_ex_name_segment() will
	 * append the segment(s)
	 */
	*temp_ptr = 0;

	return_PTR(name_string);
}