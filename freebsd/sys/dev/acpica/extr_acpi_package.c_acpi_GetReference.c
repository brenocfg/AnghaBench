#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Handle; } ;
struct TYPE_7__ {int Type; TYPE_2__ String; TYPE_1__ Reference; } ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_ANY 130 
#define  ACPI_TYPE_LOCAL_REFERENCE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

ACPI_HANDLE
acpi_GetReference(ACPI_HANDLE scope, ACPI_OBJECT *obj)
{
    ACPI_HANDLE h;

    if (obj == NULL)
	return (NULL);

    switch (obj->Type) {
    case ACPI_TYPE_LOCAL_REFERENCE:
    case ACPI_TYPE_ANY:
	h = obj->Reference.Handle;
	break;
    case ACPI_TYPE_STRING:
	/*
	 * The String object usually contains a fully-qualified path, so
	 * scope can be NULL.
	 *
	 * XXX This may not always be the case.
	 */
	if (ACPI_FAILURE(AcpiGetHandle(scope, obj->String.Pointer, &h)))
	    h = NULL;
	break;
    default:
	h = NULL;
	break;
    }

    return (h);
}