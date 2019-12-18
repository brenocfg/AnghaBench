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
 scalar_t__ ACPI_NAMESEG_SIZE ; 

__attribute__((used)) static void
UtPadNameWithUnderscores (
    char                    *NameSeg,
    char                    *PaddedNameSeg)
{
    UINT32                  i;


    for (i = 0; (i < ACPI_NAMESEG_SIZE); i++)
    {
        if (*NameSeg)
        {
            *PaddedNameSeg = *NameSeg;
            NameSeg++;
        }
        else
        {
            *PaddedNameSeg = '_';
        }

        PaddedNameSeg++;
    }
}