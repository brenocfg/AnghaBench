#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Signature; } ;
typedef  TYPE_1__ AH_TABLE ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,scalar_t__) ; 
 TYPE_1__* AcpiGbl_SupportedTables ; 

const AH_TABLE *
AcpiAhGetTableInfo (
    char                    *Signature)
{
    const AH_TABLE      *Info;


    for (Info = AcpiGbl_SupportedTables; Info->Signature; Info++)
    {
        if (ACPI_COMPARE_NAMESEG (Signature, Info->Signature))
        {
            return (Info);
        }
    }

    return (NULL);
}