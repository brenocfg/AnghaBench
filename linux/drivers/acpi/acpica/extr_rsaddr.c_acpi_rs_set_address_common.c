#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  specific_flags; } ;
union aml_resource {TYPE_4__ address; } ;
struct TYPE_5__ {int /*<<< orphan*/  type_specific; } ;
struct TYPE_6__ {scalar_t__ resource_type; TYPE_1__ info; } ;
struct TYPE_7__ {TYPE_2__ address; } ;
struct acpi_resource {TYPE_3__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_IO_RANGE ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 int /*<<< orphan*/  acpi_rs_convert_general_flags ; 
 int /*<<< orphan*/  acpi_rs_convert_io_flags ; 
 int /*<<< orphan*/  acpi_rs_convert_mem_flags ; 
 int /*<<< orphan*/  acpi_rs_convert_resource_to_aml (struct acpi_resource*,union aml_resource*,int /*<<< orphan*/ ) ; 

void
acpi_rs_set_address_common(union aml_resource *aml,
			   struct acpi_resource *resource)
{
	ACPI_FUNCTION_ENTRY();

	/* Set the Resource Type and General Flags */

	(void)acpi_rs_convert_resource_to_aml(resource, aml,
					      acpi_rs_convert_general_flags);

	/* Set the Type-Specific Flags (Memory and I/O descriptors only) */

	if (resource->data.address.resource_type == ACPI_MEMORY_RANGE) {
		(void)acpi_rs_convert_resource_to_aml(resource, aml,
						      acpi_rs_convert_mem_flags);
	} else if (resource->data.address.resource_type == ACPI_IO_RANGE) {
		(void)acpi_rs_convert_resource_to_aml(resource, aml,
						      acpi_rs_convert_io_flags);
	} else {
		/* Generic resource type, just copy the type_specific byte */

		aml->address.specific_flags =
		    resource->data.address.info.type_specific;
	}
}