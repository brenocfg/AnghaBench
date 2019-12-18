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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 char AML_ROOT_PREFIX ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmRemoveRootPrefix (
    char                    **Path)
{
    char                    *InputPath = *Path;


    if ((*InputPath == AML_ROOT_PREFIX) && (InputPath[1]))
    {
        if (!memmove(InputPath, InputPath+1, strlen(InputPath)))
        {
            return (AE_ERROR);
        }

        *Path = InputPath;
    }

    return (AE_OK);
}