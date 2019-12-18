#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int count; union acpi_object* elements; } ;
union acpi_object {TYPE_1__ package; int /*<<< orphan*/  type; } ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_object_type ;

/* Variables and functions */
 union acpi_object* ACPI_ALLOCATE_ZEROED (int) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_OK ; 
 int DB_DEFAULT_PKG_ELEMENTS ; 
 int /*<<< orphan*/  acpi_db_convert_to_object (int /*<<< orphan*/ ,char*,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_db_delete_objects (int,union acpi_object*) ; 
 char* acpi_db_get_next_token (char*,char**,int /*<<< orphan*/ *) ; 

acpi_status acpi_db_convert_to_package(char *string, union acpi_object *object)
{
	char *this;
	char *next;
	u32 i;
	acpi_object_type type;
	union acpi_object *elements;
	acpi_status status;

	elements =
	    ACPI_ALLOCATE_ZEROED(DB_DEFAULT_PKG_ELEMENTS *
				 sizeof(union acpi_object));

	this = string;
	for (i = 0; i < (DB_DEFAULT_PKG_ELEMENTS - 1); i++) {
		this = acpi_db_get_next_token(this, &next, &type);
		if (!this) {
			break;
		}

		/* Recursive call to convert each package element */

		status = acpi_db_convert_to_object(type, this, &elements[i]);
		if (ACPI_FAILURE(status)) {
			acpi_db_delete_objects(i + 1, elements);
			ACPI_FREE(elements);
			return (status);
		}

		this = next;
	}

	object->type = ACPI_TYPE_PACKAGE;
	object->package.count = i;
	object->package.elements = elements;
	return (AE_OK);
}