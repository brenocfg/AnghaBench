#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_13__ {scalar_t__ Type; } ;
struct TYPE_10__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_12__ {scalar_t__ Type; TYPE_8__* Parent; TYPE_2__ Name; } ;
struct TYPE_9__ {char* ExternalName; } ;
struct TYPE_11__ {TYPE_1__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_PROCESSOR_UID ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_SPECIAL_NAME ; 
 TYPE_8__* AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 char** AslGbl_SpecialNamedObjects ; 
 size_t MAX_SPECIAL_NAMES ; 

__attribute__((used)) static void
LdCheckSpecialNames (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  i;


    for (i = 0; i < MAX_SPECIAL_NAMES; i++)
    {
        if (ACPI_COMPARE_NAMESEG(Node->Name.Ascii, AslGbl_SpecialNamedObjects[i]) &&
            Node->Parent != AcpiGbl_RootNode)
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_SPECIAL_NAME, Op, Op->Asl.ExternalName);
            return;
        }
    }

    if (ACPI_COMPARE_NAMESEG (Node->Name.Ascii, "_UID") &&
        Node->Parent->Type == ACPI_TYPE_PROCESSOR &&
        Node->Type == ACPI_TYPE_STRING)
    {
        AslError (ASL_ERROR, ASL_MSG_INVALID_PROCESSOR_UID , Op, "found a string");
    }
}