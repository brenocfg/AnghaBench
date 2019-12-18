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
typedef  int UINT32 ;

/* Variables and functions */
 int ACPI_NUM_RTYPES ; 
 int ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/ ** UtRtypeNames ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
AcpiUtGetExpectedReturnTypes (
    char                    *Buffer,
    UINT32                  ExpectedBtypes)
{
    UINT32                  ThisRtype;
    UINT32                  i;
    UINT32                  j;


    if (!ExpectedBtypes)
    {
        strcpy (Buffer, "NONE");
        return;
    }

    j = 1;
    Buffer[0] = 0;
    ThisRtype = ACPI_RTYPE_INTEGER;

    for (i = 0; i < ACPI_NUM_RTYPES; i++)
    {
        /* If one of the expected types, concatenate the name of this type */

        if (ExpectedBtypes & ThisRtype)
        {
            strcat (Buffer, &UtRtypeNames[i][j]);
            j = 0;              /* Use name separator from now on */
        }

        ThisRtype <<= 1;    /* Next Rtype */
    }
}