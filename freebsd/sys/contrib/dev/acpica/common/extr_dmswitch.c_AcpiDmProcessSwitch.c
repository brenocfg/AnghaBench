#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int AmlOpcode; int /*<<< orphan*/  DisasmFlags; int /*<<< orphan*/  DisasmOpcode; } ;
struct TYPE_10__ {int /*<<< orphan*/  Name; } ;
struct TYPE_13__ {TYPE_2__ Common; TYPE_1__ Named; } ;
struct TYPE_12__ {struct TYPE_12__* Next; TYPE_4__* Op; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT_LIST ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 TYPE_3__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DASM_SWITCH ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_3__*) ; 
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_NAME_OP 129 
#define  AML_WHILE_OP 128 
 int /*<<< orphan*/  AcpiDmIsSwitchBlock (TYPE_4__*,char**) ; 
 TYPE_3__* AcpiGbl_TempListHead ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

ACPI_STATUS
AcpiDmProcessSwitch (
    ACPI_PARSE_OBJECT       *Op)
{
    char                    *Temp = NULL;
    ACPI_PARSE_OBJECT_LIST  *NewTemp;
    ACPI_PARSE_OBJECT_LIST  *Current;
    ACPI_PARSE_OBJECT_LIST  *Previous;
    BOOLEAN                 FoundTemp = FALSE;


    switch (Op->Common.AmlOpcode)
    {
    case AML_NAME_OP:

        Temp = (char *) (&Op->Named.Name);

        if (!strncmp(Temp, "_T_", 3))
        {
            /* Allocate and init a new Temp List node */

            NewTemp = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_PARSE_OBJECT_LIST));
            if (!NewTemp)
            {
                return (AE_NO_MEMORY);
            }

            if (AcpiGbl_TempListHead)
            {
                Current = AcpiGbl_TempListHead;
                AcpiGbl_TempListHead = NewTemp;
                AcpiGbl_TempListHead->Op = Op;
                AcpiGbl_TempListHead->Next = Current;
            }
            else
            {
                AcpiGbl_TempListHead = NewTemp;
                AcpiGbl_TempListHead->Op = Op;
                AcpiGbl_TempListHead->Next = NULL;
            }
        }
        break;

    case AML_WHILE_OP:

        if (!AcpiDmIsSwitchBlock (Op, &Temp))
        {
            break;
        }

        /* Found a Switch */

        Op->Common.DisasmOpcode = ACPI_DASM_SWITCH;

        Previous = Current = AcpiGbl_TempListHead;
        while (Current)
        {
            /* Note, if we get here Temp is not NULL */

            if (!strncmp(Temp, (char *) (&Current->Op->Named.Name), 4))
            {
                /* Match found. Ignore disassembly */

                Current->Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

                /* Remove from list */

                if (Current == AcpiGbl_TempListHead)
                {
                    AcpiGbl_TempListHead = Current->Next;
                }
                else
                {
                    Previous->Next = Current->Next;
                }

                Current->Op = NULL;
                Current->Next = NULL;
                ACPI_FREE (Current);
                FoundTemp = TRUE;
                break;
            }

            Previous = Current;
            Current = Current->Next;
        }

        if (!FoundTemp)
        {
            fprintf (stderr,
                "Warning: Declaration for temp name %.4s not found\n", Temp);
        }
        break;

    default:
        break;
    }

    return (AE_OK);
}