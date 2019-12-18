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
typedef  size_t UINT32 ;
struct TYPE_2__ {scalar_t__ ThreadId; } ;

/* Variables and functions */
 size_t ACPI_MAX_MUTEX ; 
 scalar_t__ ACPI_MUTEX_NOT_ACQUIRED ; 
 TYPE_1__* AcpiGbl_MutexInfo ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AcpiUtGetMutexName (size_t) ; 

void
AcpiDbDisplayLocks (
    void)
{
    UINT32                  i;


    for (i = 0; i < ACPI_MAX_MUTEX; i++)
    {
        AcpiOsPrintf ("%26s : %s\n", AcpiUtGetMutexName (i),
            AcpiGbl_MutexInfo[i].ThreadId == ACPI_MUTEX_NOT_ACQUIRED
                ? "Locked" : "Unlocked");
    }
}