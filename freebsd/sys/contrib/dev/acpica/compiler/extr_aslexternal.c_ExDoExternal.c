#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ Integer; } ;
struct TYPE_9__ {TYPE_3__* Next; TYPE_3__* Child; TYPE_1__ Value; int /*<<< orphan*/  ParseOpcode; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 TYPE_3__* AslGbl_ExternalsListHead ; 
 int /*<<< orphan*/  PARSEOP_BYTECONST ; 
 int /*<<< orphan*/  PARSEOP_DEFAULT_ARG ; 
 TYPE_3__* TrAllocateOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 

void
ExDoExternal (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *ListOp;
    ACPI_PARSE_OBJECT       *Prev;
    ACPI_PARSE_OBJECT       *Next;
    ACPI_PARSE_OBJECT       *ArgCountOp;


    ArgCountOp = Op->Asl.Child->Asl.Next->Asl.Next;
    ArgCountOp->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
    ArgCountOp->Asl.ParseOpcode = PARSEOP_BYTECONST;
    ArgCountOp->Asl.Value.Integer = 0;
    UtSetParseOpName (ArgCountOp);

    /* Create new list node of arbitrary type */

    ListOp = TrAllocateOp (PARSEOP_DEFAULT_ARG);

    /* Store External node as child */

    ListOp->Asl.Child = Op;
    ListOp->Asl.Next = NULL;

    if (AslGbl_ExternalsListHead)
    {
        /* Link new External to end of list */

        Prev = AslGbl_ExternalsListHead;
        Next = Prev;
        while (Next)
        {
            Prev = Next;
            Next = Next->Asl.Next;
        }

        Prev->Asl.Next = ListOp;
    }
    else
    {
        AslGbl_ExternalsListHead = ListOp;
    }
}