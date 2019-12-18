#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_4__ {int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 TYPE_1__* AslGbl_CurrentField ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtEvaluateExpression (int /*<<< orphan*/ ) ; 

ACPI_STATUS
DtResolveIntegerExpression (
    DT_FIELD                *Field,
    UINT64                  *ReturnValue)
{
    UINT64                  Result;


    DbgPrint (ASL_DEBUG_OUTPUT, "Full Integer expression: %s\n",
        Field->Value);

    AslGbl_CurrentField = Field;

    Result = DtEvaluateExpression (Field->Value);
    *ReturnValue = Result;
    return (AE_OK);
}