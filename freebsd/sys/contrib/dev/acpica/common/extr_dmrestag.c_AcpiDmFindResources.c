#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ AmlOpcode; int /*<<< orphan*/  Node; int /*<<< orphan*/  DisasmOpcode; TYPE_2__* Parent; } ;
struct TYPE_10__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DASM_RESOURCE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ AML_BUFFER_OP ; 
 scalar_t__ AML_NAME_OP ; 
 int /*<<< orphan*/  AcpiDmAddResourcesToNamespace (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDmIsResourceTemplate (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* AcpiPsGetDepthNext (TYPE_2__*,TYPE_2__*) ; 

void
AcpiDmFindResources (
    ACPI_PARSE_OBJECT       *Root)
{
    ACPI_PARSE_OBJECT       *Op = Root;
    ACPI_PARSE_OBJECT       *Parent;


    /* Walk the entire parse tree */

    while (Op)
    {
        /* We are interested in Buffer() declarations */

        if (Op->Common.AmlOpcode == AML_BUFFER_OP)
        {
            /* And only declarations of the form Name (XXXX, Buffer()... ) */

            Parent = Op->Common.Parent;
            if (Parent->Common.AmlOpcode == AML_NAME_OP)
            {
                /*
                 * If the buffer is a resource template, add the individual
                 * resource descriptors to the namespace, as children of the
                 * buffer node.
                 */
                if (ACPI_SUCCESS (AcpiDmIsResourceTemplate (NULL, Op)))
                {
                    Op->Common.DisasmOpcode = ACPI_DASM_RESOURCE;
                    AcpiDmAddResourcesToNamespace (Parent->Common.Node, Op);
                }
            }
        }

        Op = AcpiPsGetDepthNext (Root, Op);
    }
}