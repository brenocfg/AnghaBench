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
typedef  int UINT32 ;
struct TYPE_5__ {int ParseOpcode; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int ACPI_NOT_PACKAGE_ELEMENT ; 
 int ACPI_RTYPE_BUFFER ; 
 int ACPI_RTYPE_INTEGER ; 
 int ACPI_RTYPE_PACKAGE ; 
 int ACPI_RTYPE_REFERENCE ; 
 int ACPI_RTYPE_STRING ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_OPERAND_TYPE ; 
 int /*<<< orphan*/  AcpiUtGetExpectedReturnTypes (char*,int) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 char* AslGbl_StringBuffer ; 
#define  PARSEOP_BUFFER 137 
#define  PARSEOP_INTEGER 136 
#define  PARSEOP_NAMESEG 135 
#define  PARSEOP_NAMESTRING 134 
#define  PARSEOP_ONE 133 
#define  PARSEOP_ONES 132 
#define  PARSEOP_PACKAGE 131 
#define  PARSEOP_STRING_LITERAL 130 
#define  PARSEOP_VAR_PACKAGE 129 
#define  PARSEOP_ZERO 128 
 char* UtGetOpName (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 

ACPI_STATUS
ApCheckObjectType (
    const char              *PredefinedName,
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  ExpectedBtypes,
    UINT32                  PackageIndex)
{
    UINT32                  ReturnBtype;
    char                    *TypeName;


    if (!Op)
    {
        return (AE_TYPE);
    }

    /* Map the parse opcode to a bitmapped return type (RTYPE) */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_ZERO:
    case PARSEOP_ONE:
    case PARSEOP_ONES:
    case PARSEOP_INTEGER:

        ReturnBtype = ACPI_RTYPE_INTEGER;
        TypeName = "Integer";
        break;

    case PARSEOP_STRING_LITERAL:

        ReturnBtype = ACPI_RTYPE_STRING;
        TypeName = "String";
        break;

    case PARSEOP_BUFFER:

        ReturnBtype = ACPI_RTYPE_BUFFER;
        TypeName = "Buffer";
        break;

    case PARSEOP_PACKAGE:
    case PARSEOP_VAR_PACKAGE:

        ReturnBtype = ACPI_RTYPE_PACKAGE;
        TypeName = "Package";
        break;

    case PARSEOP_NAMESEG:
    case PARSEOP_NAMESTRING:
        /*
         * Ignore any named references within a package object.
         *
         * For Package objects, references are allowed instead of any of the
         * standard data types (Integer/String/Buffer/Package). These
         * references are resolved at runtime. NAMESEG and NAMESTRING are
         * impossible to typecheck at compile time because the type of
         * any named object can be changed at runtime (for example,
         * CopyObject will change the type of the target object).
         */
        if (PackageIndex != ACPI_NOT_PACKAGE_ELEMENT)
        {
            return (AE_OK);
        }

        ReturnBtype = ACPI_RTYPE_REFERENCE;
        TypeName = "Reference";
        break;

    default:

        /* Not one of the supported object types */

        TypeName = UtGetOpName (Op->Asl.ParseOpcode);
        goto TypeErrorExit;
    }

    /* Exit if the object is one of the expected types */

    if (ReturnBtype & ExpectedBtypes)
    {
        return (AE_OK);
    }


TypeErrorExit:

    /* Format the expected types and emit an error message */

    AcpiUtGetExpectedReturnTypes (AslGbl_StringBuffer, ExpectedBtypes);

    if (PackageIndex == ACPI_NOT_PACKAGE_ELEMENT)
    {
        sprintf (AslGbl_MsgBuffer, "%4.4s: found %s, %s required",
            PredefinedName, TypeName, AslGbl_StringBuffer);
    }
    else
    {
        sprintf (AslGbl_MsgBuffer, "%4.4s: found %s at index %u, %s required",
            PredefinedName, TypeName, PackageIndex, AslGbl_StringBuffer);
    }

    AslError (ASL_ERROR, ASL_MSG_RESERVED_OPERAND_TYPE, Op, AslGbl_MsgBuffer);
    return (AE_TYPE);
}