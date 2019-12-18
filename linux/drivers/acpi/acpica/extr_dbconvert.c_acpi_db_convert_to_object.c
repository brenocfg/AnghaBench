#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {char* pointer; int /*<<< orphan*/  length; } ;
union acpi_object {int type; TYPE_1__ integer; TYPE_2__ string; } ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;

/* Variables and functions */
#define  ACPI_TYPE_BUFFER 130 
 int ACPI_TYPE_INTEGER ; 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_convert_to_buffer (char*,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_db_convert_to_package (char*,union acpi_object*) ; 
 int /*<<< orphan*/  acpi_ut_strtoul64 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

acpi_status
acpi_db_convert_to_object(acpi_object_type type,
			  char *string, union acpi_object *object)
{
	acpi_status status = AE_OK;

	switch (type) {
	case ACPI_TYPE_STRING:

		object->type = ACPI_TYPE_STRING;
		object->string.pointer = string;
		object->string.length = (u32)strlen(string);
		break;

	case ACPI_TYPE_BUFFER:

		status = acpi_db_convert_to_buffer(string, object);
		break;

	case ACPI_TYPE_PACKAGE:

		status = acpi_db_convert_to_package(string, object);
		break;

	default:

		object->type = ACPI_TYPE_INTEGER;
		status = acpi_ut_strtoul64(string, &object->integer.value);
		break;
	}

	return (status);
}