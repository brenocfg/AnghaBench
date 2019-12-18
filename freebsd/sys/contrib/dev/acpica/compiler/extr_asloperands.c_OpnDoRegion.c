#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_11__ {scalar_t__ ParseOpcode; TYPE_3__ Value; TYPE_5__* Next; TYPE_5__* Child; } ;
struct TYPE_8__ {scalar_t__ Integer; } ;
struct TYPE_9__ {TYPE_1__ Value; } ;
struct TYPE_12__ {TYPE_4__ Asl; TYPE_2__ Common; } ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  scalar_t__ ACPI_ADR_SPACE_TYPE ;

/* Variables and functions */
 scalar_t__ ACPI_NUM_PREDEFINED_REGIONS ; 
 int /*<<< orphan*/  ACPI_UINT64_MAX ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_REGION_LENGTH ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ PARSEOP_INTEGER ; 

__attribute__((used)) static void
OpnDoRegion (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    ACPI_ADR_SPACE_TYPE     SpaceId;


    /* Opcode is parent node */
    /* First child is the region name */

    Next = Op->Asl.Child;

    /* Second child is the space ID */

    Next = Next->Asl.Next;
    SpaceId = (ACPI_ADR_SPACE_TYPE) Next->Common.Value.Integer;

    /* Third child is the region offset */

    Next = Next->Asl.Next;

    /* Fourth child is the region length */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode == PARSEOP_INTEGER)
    {
        /* Check for zero length */

        Op->Asl.Value.Integer = Next->Asl.Value.Integer;
        if (!Op->Asl.Value.Integer && (SpaceId < ACPI_NUM_PREDEFINED_REGIONS))
        {
            AslError (ASL_ERROR, ASL_MSG_REGION_LENGTH, Op, NULL);
        }
    }
    else
    {
        Op->Asl.Value.Integer = ACPI_UINT64_MAX;
    }
}