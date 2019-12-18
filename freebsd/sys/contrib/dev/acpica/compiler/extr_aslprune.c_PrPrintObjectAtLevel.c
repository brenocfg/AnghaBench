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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

__attribute__((used)) static void
PrPrintObjectAtLevel (
    UINT32                  Level,
    const char              *ObjectName)
{
    UINT32                  i;


    for (i = 0; i < Level; i++)
    {
        AcpiOsPrintf ("  ");
    }

    AcpiOsPrintf ("[%s] at Level [%u]\n", ObjectName, Level);
}