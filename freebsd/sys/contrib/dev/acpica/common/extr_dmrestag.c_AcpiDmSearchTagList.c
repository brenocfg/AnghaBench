#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_3__ {char* Tag; scalar_t__ BitIndex; } ;
typedef  TYPE_1__ ACPI_RESOURCE_TAG ;

/* Variables and functions */

__attribute__((used)) static char *
AcpiDmSearchTagList (
    UINT32                  BitIndex,
    const ACPI_RESOURCE_TAG *TagList)
{

    /*
     * Walk the null-terminated tag list to find a matching bit offset.
     * We are looking for an exact match.
     */
    for ( ; TagList->Tag; TagList++)
    {
        if (BitIndex == TagList->BitIndex)
        {
            return (TagList->Tag);
        }
    }

    /* A matching offset was not found */

    return (NULL);
}