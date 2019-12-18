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
struct TYPE_4__ {struct TYPE_4__* NextLabel; int /*<<< orphan*/  TableOffset; int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 TYPE_1__* AslGbl_LabelList ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DtInsertLabelField (
    DT_FIELD                *Field)
{

    DbgPrint (ASL_DEBUG_OUTPUT,
        "DtInsertLabelField: Found Label : %s at output table offset %X\n",
        Field->Value, Field->TableOffset);

    Field->NextLabel = AslGbl_LabelList;
    AslGbl_LabelList = Field;
}