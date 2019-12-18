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
struct TYPE_4__ {scalar_t__ Name; } ;
typedef  TYPE_1__ AH_PREDEFINED_NAME ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,scalar_t__) ; 
 TYPE_1__* AslPredefinedInfo ; 

const AH_PREDEFINED_NAME *
AcpiAhMatchPredefinedName (
    char                        *Nameseg)
{
    const AH_PREDEFINED_NAME    *Info;


    /* Nameseg must start with an underscore */

    if (*Nameseg != '_')
    {
        return (NULL);
    }

    /* Search for a match in the predefined name table */

    for (Info = AslPredefinedInfo; Info->Name; Info++)
    {
        if (ACPI_COMPARE_NAMESEG (Nameseg, Info->Name))
        {
            return (Info);
        }
    }

    return (NULL);
}