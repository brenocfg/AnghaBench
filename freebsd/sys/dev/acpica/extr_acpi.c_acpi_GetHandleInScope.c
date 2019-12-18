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
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiGetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ACPI_STATUS
acpi_GetHandleInScope(ACPI_HANDLE parent, char *path, ACPI_HANDLE *result)
{
    ACPI_HANDLE		r;
    ACPI_STATUS		status;

    /* Walk back up the tree to the root */
    for (;;) {
	status = AcpiGetHandle(parent, path, &r);
	if (ACPI_SUCCESS(status)) {
	    *result = r;
	    return (AE_OK);
	}
	/* XXX Return error here? */
	if (status != AE_NOT_FOUND)
	    return (AE_OK);
	if (ACPI_FAILURE(AcpiGetParent(parent, &r)))
	    return (AE_NOT_FOUND);
	parent = r;
    }
}