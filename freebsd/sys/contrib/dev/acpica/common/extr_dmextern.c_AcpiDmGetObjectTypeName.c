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
typedef  size_t ACPI_OBJECT_TYPE ;

/* Variables and functions */
 size_t ACPI_TYPE_DEVICE ; 
 size_t ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 size_t ACPI_TYPE_LOCAL_SCOPE ; 
 char const** AcpiGbl_DmTypeNames ; 

__attribute__((used)) static const char *
AcpiDmGetObjectTypeName (
    ACPI_OBJECT_TYPE        Type)
{

    if (Type == ACPI_TYPE_LOCAL_SCOPE)
    {
        Type = ACPI_TYPE_DEVICE;
    }
    else if (Type > ACPI_TYPE_LOCAL_INDEX_FIELD)
    {
        return ("");
    }

    return (AcpiGbl_DmTypeNames[Type]);
}