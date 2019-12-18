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
struct TYPE_4__ {char* FileStart; char* FileEnd; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ACPI_FILE_NODE ;

/* Variables and functions */

__attribute__((used)) static ACPI_FILE_NODE *
CvFileAddressLookup(
    char                    *Address,
    ACPI_FILE_NODE          *Head)
{
    ACPI_FILE_NODE          *Current = Head;


    while (Current)
    {
        if ((Address >= Current->FileStart) &&
            (Address < Current->FileEnd ||
            !Current->FileEnd))
        {
            return (Current);
        }

        Current = Current->Next;
    }

    return (NULL);
}