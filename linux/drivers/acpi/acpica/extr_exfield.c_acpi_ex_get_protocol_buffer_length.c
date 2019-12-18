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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_INVALID_PROTOCOL_ID ; 
 size_t ACPI_MAX_PROTOCOL_ID ; 
 int /*<<< orphan*/  AE_AML_PROTOCOL ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__* acpi_protocol_lengths ; 

acpi_status
acpi_ex_get_protocol_buffer_length(u32 protocol_id, u32 *return_length)
{

	if ((protocol_id > ACPI_MAX_PROTOCOL_ID) ||
	    (acpi_protocol_lengths[protocol_id] == ACPI_INVALID_PROTOCOL_ID)) {
		ACPI_ERROR((AE_INFO,
			    "Invalid Field/AccessAs protocol ID: 0x%4.4X",
			    protocol_id));

		return (AE_AML_PROTOCOL);
	}

	*return_length = acpi_protocol_lengths[protocol_id];
	return (AE_OK);
}