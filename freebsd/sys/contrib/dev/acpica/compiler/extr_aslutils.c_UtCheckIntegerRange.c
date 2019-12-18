#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {scalar_t__ Integer; } ;
struct TYPE_8__ {TYPE_1__ Value; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_RANGE ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 

ACPI_PARSE_OBJECT *
UtCheckIntegerRange (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  LowValue,
    UINT32                  HighValue)
{

    if (!Op)
    {
        return (NULL);
    }

    if ((Op->Asl.Value.Integer < LowValue) ||
        (Op->Asl.Value.Integer > HighValue))
    {
        sprintf (AslGbl_MsgBuffer, "0x%X, allowable: 0x%X-0x%X",
            (UINT32) Op->Asl.Value.Integer, LowValue, HighValue);

        AslError (ASL_ERROR, ASL_MSG_RANGE, Op, AslGbl_MsgBuffer);
        return (NULL);
    }

    return (Op);
}