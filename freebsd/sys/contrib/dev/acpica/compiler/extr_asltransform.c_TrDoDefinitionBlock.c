#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_6__ {int /*<<< orphan*/  String; } ;
struct TYPE_7__ {TYPE_1__ Value; TYPE_3__* Next; TYPE_3__* Child; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/ * AslGbl_ExternalsListHead ; 
 TYPE_3__* AslGbl_FirstLevelInsertionNode ; 
 int /*<<< orphan*/  AslGbl_ReferenceOptimizationFlag ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static void
TrDoDefinitionBlock (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    UINT32                  i;


    /* Reset external list when starting a definition block */

    AslGbl_ExternalsListHead = NULL;

    Next = Op->Asl.Child;
    for (i = 0; i < 5; i++)
    {
        Next = Next->Asl.Next;
        if (i == 0)
        {
            /*
             * This is the table signature. Only the DSDT can be assumed
             * to be at the root of the namespace;  Therefore, namepath
             * optimization can only be performed on the DSDT.
             */
            if (!ACPI_COMPARE_NAMESEG (Next->Asl.Value.String, ACPI_SIG_DSDT))
            {
                AslGbl_ReferenceOptimizationFlag = FALSE;
            }
        }
    }

    AslGbl_FirstLevelInsertionNode = Next;
}