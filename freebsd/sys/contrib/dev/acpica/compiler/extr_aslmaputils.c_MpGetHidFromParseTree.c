#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* Op; } ;
struct TYPE_6__ {char* String; int /*<<< orphan*/  Integer; } ;
struct TYPE_7__ {int ParseOpcode; TYPE_1__ Value; TYPE_3__* Next; TYPE_3__* Child; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EISAID_STRING_SIZE ; 
 int /*<<< orphan*/  AcpiExEisaIdToString (char*,int /*<<< orphan*/ ) ; 
#define  PARSEOP_INTEGER 130 
#define  PARSEOP_NAME 129 
#define  PARSEOP_STRING_LITERAL 128 
 char* UtLocalCacheCalloc (int /*<<< orphan*/ ) ; 

char *
MpGetHidFromParseTree (
    ACPI_NAMESPACE_NODE     *HidNode)
{
    ACPI_PARSE_OBJECT       *Op;
    ACPI_PARSE_OBJECT       *Arg;
    char                    *HidString;


    Op = HidNode->Op;
    if (!Op)
    {
        /* Object is not resolved, probably an External */

        return ("Unresolved Symbol - referenced but not defined in this table");
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_NAME:

        Arg = Op->Asl.Child;  /* Get the NameSeg/NameString node */
        Arg = Arg->Asl.Next;  /* First peer is the object to be associated with the name */

        switch (Arg->Asl.ParseOpcode)
        {
        case PARSEOP_STRING_LITERAL:

            return (Arg->Asl.Value.String);

        case PARSEOP_INTEGER:

            /* Convert EISAID to a string */

            HidString = UtLocalCacheCalloc (ACPI_EISAID_STRING_SIZE);
            AcpiExEisaIdToString (HidString, Arg->Asl.Value.Integer);
            return (HidString);

        default:

            return ("UNKNOWN");
        }

    default:
        return ("-No HID-");
    }
}