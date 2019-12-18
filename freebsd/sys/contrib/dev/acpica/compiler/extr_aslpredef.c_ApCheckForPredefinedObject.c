#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_17__ {scalar_t__ ParseOpcode; TYPE_2__* Child; } ;
struct TYPE_19__ {TYPE_4__ Asl; } ;
struct TYPE_16__ {int /*<<< orphan*/  ExpectedBtypes; int /*<<< orphan*/  Name; int /*<<< orphan*/  ArgumentList; } ;
struct TYPE_18__ {TYPE_3__ Info; } ;
struct TYPE_14__ {TYPE_6__* Next; } ;
struct TYPE_15__ {TYPE_1__ Asl; } ;
typedef  TYPE_5__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  ACPI_COMPILER_RESERVED_NAME 131 
#define  ACPI_EVENT_RESERVED_NAME 130 
 int /*<<< orphan*/  ACPI_NOT_PACKAGE_ELEMENT ; 
#define  ACPI_NOT_RESERVED_NAME 129 
#define  ACPI_PREDEFINED_NAME 128 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_METHOD ; 
 TYPE_5__* AcpiGbl_PredefinedMethods ; 
 int ApCheckForPredefinedName (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  ApCheckObjectType (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApCheckPackage (TYPE_6__*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,char*) ; 
 scalar_t__ METHOD_GET_ARG_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ PARSEOP_PACKAGE ; 

void
ApCheckForPredefinedObject (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Name)
{
    UINT32                      Index;
    ACPI_PARSE_OBJECT           *ObjectOp;
    const ACPI_PREDEFINED_INFO  *ThisName;


    /*
     * Check for a real predefined name -- not a resource descriptor name
     * or a predefined scope name
     */
    Index = ApCheckForPredefinedName (Op, Name);

    switch (Index)
    {
    case ACPI_NOT_RESERVED_NAME:        /* No underscore or _Txx or _xxx name not matched */
    case ACPI_PREDEFINED_NAME:          /* Resource Name or reserved scope name */
    case ACPI_COMPILER_RESERVED_NAME:   /* A _Txx that was not emitted by compiler */

        /* Nothing to do */
        return;

    case ACPI_EVENT_RESERVED_NAME:      /* _Lxx/_Exx/_Wxx/_Qxx methods */

        /*
         * These names must be control methods, by definition in ACPI spec.
         * Also because they are defined to return no value. None of them
         * require any arguments.
         */
        AslError (ASL_ERROR, ASL_MSG_RESERVED_METHOD, Op,
            "with zero arguments");
        return;

    default:

        break;
    }

    /* A standard predefined ACPI name */

    /*
     * If this predefined name requires input arguments, then
     * it must be implemented as a control method
     */
    ThisName = &AcpiGbl_PredefinedMethods[Index];
    if (METHOD_GET_ARG_COUNT (ThisName->Info.ArgumentList) > 0)
    {
        AslError (ASL_ERROR, ASL_MSG_RESERVED_METHOD, Op,
            "with arguments");
        return;
    }

    /*
     * If no return value is expected from this predefined name, then
     * it follows that it must be implemented as a control method
     * (with zero args, because the args > 0 case was handled above)
     * Examples are: _DIS, _INI, _IRC, _OFF, _ON, _PSx
     */
    if (!ThisName->Info.ExpectedBtypes)
    {
        AslError (ASL_ERROR, ASL_MSG_RESERVED_METHOD, Op,
            "with zero arguments");
        return;
    }

    /* Typecheck the actual object, it is the next argument */

    ObjectOp = Op->Asl.Child->Asl.Next;
    ApCheckObjectType (ThisName->Info.Name, Op->Asl.Child->Asl.Next,
        ThisName->Info.ExpectedBtypes, ACPI_NOT_PACKAGE_ELEMENT);

    /* For packages, check the individual package elements */

    if (ObjectOp->Asl.ParseOpcode == PARSEOP_PACKAGE)
    {
        ApCheckPackage (ObjectOp, ThisName);
    }
}