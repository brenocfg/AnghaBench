#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Count; TYPE_2__* Elements; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 

ACPI_STATUS
acpi_ForeachPackageObject(ACPI_OBJECT *pkg,
	void (*func)(ACPI_OBJECT *comp, void *arg), void *arg)
{
    ACPI_OBJECT	*comp;
    int		i;

    if (pkg == NULL || pkg->Type != ACPI_TYPE_PACKAGE)
	return (AE_BAD_PARAMETER);

    /* Iterate over components */
    i = 0;
    comp = pkg->Package.Elements;
    for (; i < pkg->Package.Count; i++, comp++)
	func(comp, arg);

    return (AE_OK);
}