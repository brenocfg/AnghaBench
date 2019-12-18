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
typedef  size_t UINT64 ;
typedef  size_t UINT32 ;

/* Variables and functions */

__attribute__((used)) static const char *
AcpiDmFindNameByIndex (
    UINT64                  Index,
    const char              **List)
{
    const char              *NameString;
    UINT32                  i;


    /* Bounds check */

    NameString = List[0];
    i = 0;

    while (NameString)
    {
        i++;
        NameString = List[i];
    }

    if (Index >= i)
    {
        /* TBD: Add error msg */

        return ("");
    }

    return (List[Index]);
}