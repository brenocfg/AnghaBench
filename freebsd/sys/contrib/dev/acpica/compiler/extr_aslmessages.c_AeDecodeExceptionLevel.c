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
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t ACPI_ARRAY_LENGTH (char const**) ; 
 char const** AslErrorLevel ; 
 char const** AslErrorLevelIde ; 
 scalar_t__ AslGbl_VerboseErrors ; 

const char *
AeDecodeExceptionLevel (
    UINT8                   Level)
{
    /* Range check on Level */

    if (Level >= ACPI_ARRAY_LENGTH (AslErrorLevel))
    {
        return ("Unknown exception level");
    }

    /* Differentiate the string type to be used (IDE is all lower case) */

    if (AslGbl_VerboseErrors)
    {
        return (AslErrorLevel[Level]);
    }

    return (AslErrorLevelIde[Level]);
}