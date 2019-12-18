#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_13__ {scalar_t__ Integer; } ;
struct TYPE_14__ {scalar_t__ ParseOpcode; TYPE_1__ Value; TYPE_5__* Next; TYPE_5__* Child; } ;
struct TYPE_17__ {TYPE_2__ Asl; } ;
struct TYPE_15__ {int /*<<< orphan*/  Name; } ;
struct TYPE_16__ {TYPE_3__ Info; } ;
typedef  TYPE_4__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_RTYPE_STRING ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_OPERAND_TYPE ; 
 TYPE_5__* ApCheckPackageElements (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ApPackageTooLarge (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ApPackageTooSmall (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 scalar_t__ PARSEOP_INTEGER ; 

__attribute__((used)) static void
ApCustomPackage (
    ACPI_PARSE_OBJECT           *ParentOp,
    const ACPI_PREDEFINED_INFO  *Predefined)
{
    ACPI_PARSE_OBJECT           *Op;
    UINT32                      Count;
    UINT32                      ExpectedCount;
    UINT32                      Version;


    /* First child is the package length */

    Op = ParentOp->Asl.Child;
    Count = (UINT32) Op->Asl.Value.Integer;

    /* Get the version number, must be Integer */

    Op = Op->Asl.Next;
    Version = (UINT32) Op->Asl.Value.Integer;
    if (Op->Asl.ParseOpcode != PARSEOP_INTEGER)
    {
        AslError (ASL_ERROR, ASL_MSG_RESERVED_OPERAND_TYPE, Op, AslGbl_MsgBuffer);
        return;
    }

    /* Validate count (# of elements) */

    ExpectedCount = 21;         /* Version 1 */
    if (Version == 0)
    {
        ExpectedCount = 20;     /* Version 0 */
    }

    if (Count < ExpectedCount)
    {
        ApPackageTooSmall (Predefined->Info.Name, ParentOp,
            Count, ExpectedCount);
        return;
    }
    else if (Count > ExpectedCount)
    {
        ApPackageTooLarge (Predefined->Info.Name, ParentOp,
            Count, ExpectedCount);
    }

    /* Validate all elements of the package */

    Op = ApCheckPackageElements (Predefined->Info.Name, Op,
        ACPI_RTYPE_INTEGER, 16,
        ACPI_RTYPE_STRING, 4);

    /* Version 1 has a single trailing integer */

    if (Version > 0)
    {
        ApCheckPackageElements (Predefined->Info.Name, Op,
            ACPI_RTYPE_INTEGER, 1, 0, 0);
    }
}