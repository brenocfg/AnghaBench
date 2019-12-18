#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {char* NameSeg; scalar_t__ ParseOpcode; TYPE_2__* Next; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,char*) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (char*,char*) ; 
 int ACPI_NAMESEG_SIZE ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_GPE_NAME_CONFLICT ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 scalar_t__ PARSEOP_METHOD ; 
 scalar_t__ PARSEOP_NAME ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

void
ApCheckForGpeNameConflict (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  GpeNumber;
    char                    Name[ACPI_NAMESEG_SIZE + 1];
    char                    Target[ACPI_NAMESEG_SIZE];


    /* Need a null-terminated string version of NameSeg */

    ACPI_MOVE_32_TO_32 (Name, Op->Asl.NameSeg);
    Name[ACPI_NAMESEG_SIZE] = 0;

    /*
     * For a GPE method:
     * 1st char must be underscore
     * 2nd char must be L or E
     * 3rd/4th chars must be a hex number
     */
    if ((Name[0] != '_') ||
       ((Name[1] != 'L') && (Name[1] != 'E')))
    {
        return;
    }

    /* Verify 3rd/4th chars are a valid hex value */

    GpeNumber = strtoul (&Name[2], NULL, 16);
    if (GpeNumber == ACPI_UINT32_MAX)
    {
        return;
    }

    /*
     * We are now sure we have an _Lxx or _Exx.
     * Create the target name that would cause collision (Flip E/L)
     */
    ACPI_MOVE_32_TO_32 (Target, Name);

    /* Inject opposite letter ("L" versus "E") */

    if (Name[1] == 'L')
    {
        Target[1] = 'E';
    }
    else /* Name[1] == 'E' */
    {
        Target[1] = 'L';
    }

    /* Search all peers (objects within this scope) for target match */

    NextOp = Op->Asl.Next;
    while (NextOp)
    {
        /*
         * We mostly care about methods, but check Name() constructs also,
         * even though they will get another error for not being a method.
         * All GPE names must be defined as control methods.
         */
        if ((NextOp->Asl.ParseOpcode == PARSEOP_METHOD) ||
            (NextOp->Asl.ParseOpcode == PARSEOP_NAME))
        {
            if (ACPI_COMPARE_NAMESEG (Target, NextOp->Asl.NameSeg))
            {
                /* Found both _Exy and _Lxy in the same scope, error */

                AslError (ASL_ERROR, ASL_MSG_GPE_NAME_CONFLICT, NextOp,
                    Name);
                return;
            }
        }

        NextOp = NextOp->Asl.Next;
    }

    /* OK, no conflict found */

    return;
}