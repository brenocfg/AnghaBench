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
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ Integer; int /*<<< orphan*/  String; } ;
struct TYPE_7__ {int CompileFlags; TYPE_1__ Value; TYPE_3__* Next; TYPE_3__* Child; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  Node; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 char* AcpiNsGetNormalizedPathname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* AslGbl_ExternalsListHead ; 
 int OP_VISITED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtInternalizeName (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExInsertArgCount (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    ACPI_PARSE_OBJECT       *NameOp;
    ACPI_PARSE_OBJECT       *Child;
    ACPI_PARSE_OBJECT       *ArgCountOp;
    char *                  ExternalName;
    char *                  CallName;
    UINT16                  ArgCount = 0;
    ACPI_STATUS             Status;


    CallName = AcpiNsGetNormalizedPathname (Op->Asl.Node, TRUE);

    Next = AslGbl_ExternalsListHead;
    while (Next)
    {
        ArgCount = 0;

        /* Skip if External node already handled */

        if (Next->Asl.Child->Asl.CompileFlags & OP_VISITED)
        {
            Next = Next->Asl.Next;
            continue;
        }

        NameOp = Next->Asl.Child->Asl.Child;
        ExternalName = AcpiNsGetNormalizedPathname (NameOp->Asl.Node, TRUE);

        if (strcmp (CallName, ExternalName))
        {
            ACPI_FREE (ExternalName);
            Next = Next->Asl.Next;
            continue;
        }

        Next->Asl.Child->Asl.CompileFlags |= OP_VISITED;

        /*
         * Since we will reposition Externals to the Root, set Namepath
         * to the fully qualified name and recalculate the aml length
         */
        Status = UtInternalizeName (ExternalName,
            &NameOp->Asl.Value.String);

        ACPI_FREE (ExternalName);
        if (ACPI_FAILURE (Status))
        {
            AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL,
                NULL, "- Could not Internalize External");
            break;
        }

        NameOp->Asl.AmlLength = strlen (NameOp->Asl.Value.String);

        /* Get argument count */

        Child = Op->Asl.Child;
        while (Child)
        {
            ArgCount++;
            Child = Child->Asl.Next;
        }

        /* Setup ArgCount operand */

        ArgCountOp = Next->Asl.Child->Asl.Child->Asl.Next->Asl.Next;
        ArgCountOp->Asl.Value.Integer = ArgCount;
        break;
    }

    ACPI_FREE (CallName);
}