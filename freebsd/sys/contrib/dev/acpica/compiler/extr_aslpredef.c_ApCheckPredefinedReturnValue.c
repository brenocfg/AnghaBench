#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_19__ {int const ParseOpcode; TYPE_6__* Child; } ;
struct TYPE_22__ {TYPE_3__ Asl; } ;
struct TYPE_18__ {int /*<<< orphan*/  ExpectedBtypes; int /*<<< orphan*/  Name; } ;
struct TYPE_21__ {TYPE_2__ Info; } ;
struct TYPE_20__ {TYPE_14__* Op; } ;
struct TYPE_17__ {int /*<<< orphan*/  NameSeg; } ;
struct TYPE_16__ {TYPE_1__ Asl; } ;
typedef  TYPE_4__ ASL_METHOD_INFO ;
typedef  TYPE_5__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  ACPI_COMPILER_RESERVED_NAME 138 
#define  ACPI_EVENT_RESERVED_NAME 137 
 int /*<<< orphan*/  ACPI_NOT_PACKAGE_ELEMENT ; 
#define  ACPI_NOT_RESERVED_NAME 136 
#define  ACPI_PREDEFINED_NAME 135 
 TYPE_5__* AcpiGbl_PredefinedMethods ; 
 int ApCheckForPredefinedName (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApCheckForUnexpectedReturnValue (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ApCheckObjectType (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApCheckPackage (TYPE_6__*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  AslGbl_AllExceptionsDisabled ; 
 int /*<<< orphan*/  FALSE ; 
#define  PARSEOP_BUFFER 134 
#define  PARSEOP_INTEGER 133 
#define  PARSEOP_ONE 132 
#define  PARSEOP_ONES 131 
#define  PARSEOP_PACKAGE 130 
#define  PARSEOP_STRING_LITERAL 129 
#define  PARSEOP_ZERO 128 
 int /*<<< orphan*/  TRUE ; 

void
ApCheckPredefinedReturnValue (
    ACPI_PARSE_OBJECT       *Op,
    ASL_METHOD_INFO         *MethodInfo)
{
    UINT32                      Index;
    ACPI_PARSE_OBJECT           *ReturnValueOp;
    const ACPI_PREDEFINED_INFO  *ThisName;


    /*
     * Check parent method for a match against the predefined name list.
     *
     * Note: Disable compiler errors/warnings because any errors will be
     * caught when analyzing the parent method. Eliminates duplicate errors.
     */
    AslGbl_AllExceptionsDisabled = TRUE;
    Index = ApCheckForPredefinedName (MethodInfo->Op,
        MethodInfo->Op->Asl.NameSeg);
    AslGbl_AllExceptionsDisabled = FALSE;

    switch (Index)
    {
    case ACPI_EVENT_RESERVED_NAME:      /* _Lxx/_Exx/_Wxx/_Qxx methods */

        /* No return value expected, warn if there is one */

        ApCheckForUnexpectedReturnValue (Op, MethodInfo);
        return;

    case ACPI_NOT_RESERVED_NAME:        /* No underscore or _Txx or _xxx name not matched */
    case ACPI_PREDEFINED_NAME:          /* Resource Name or reserved scope name */
    case ACPI_COMPILER_RESERVED_NAME:   /* A _Txx that was not emitted by compiler */

        /* Just return, nothing to do */
        return;

    default: /* A standard predefined ACPI name */

        ThisName = &AcpiGbl_PredefinedMethods[Index];
        if (!ThisName->Info.ExpectedBtypes)
        {
            /* No return value expected, warn if there is one */

            ApCheckForUnexpectedReturnValue (Op, MethodInfo);
            return;
        }

        /* Get the object returned, it is the next argument */

        ReturnValueOp = Op->Asl.Child;
        switch (ReturnValueOp->Asl.ParseOpcode)
        {
        case PARSEOP_ZERO:
        case PARSEOP_ONE:
        case PARSEOP_ONES:
        case PARSEOP_INTEGER:
        case PARSEOP_STRING_LITERAL:
        case PARSEOP_BUFFER:
        case PARSEOP_PACKAGE:

            /* Static data return object - check against expected type */

            ApCheckObjectType (ThisName->Info.Name, ReturnValueOp,
                ThisName->Info.ExpectedBtypes, ACPI_NOT_PACKAGE_ELEMENT);

            /* For packages, check the individual package elements */

            if (ReturnValueOp->Asl.ParseOpcode == PARSEOP_PACKAGE)
            {
                ApCheckPackage (ReturnValueOp, ThisName);
            }
            break;

        default:
            /*
             * All other ops are very difficult or impossible to typecheck at
             * compile time. These include all Localx, Argx, and method
             * invocations. Also, NAMESEG and NAMESTRING because the type of
             * any named object can be changed at runtime (for example,
             * CopyObject will change the type of the target object.)
             */
            break;
        }
    }
}