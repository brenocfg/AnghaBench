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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_12__ {TYPE_4__* Op; } ;
struct TYPE_9__ {scalar_t__ Integer; TYPE_4__* Arg; } ;
struct TYPE_10__ {TYPE_2__ Value; TYPE_5__* Node; TYPE_4__* Next; } ;
struct TYPE_8__ {scalar_t__ Data; } ;
struct TYPE_11__ {TYPE_3__ Common; TYPE_1__ Named; } ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmAddResourceToNamespace ; 
 int /*<<< orphan*/  AcpiUtWalkAmlResources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void
AcpiDmAddResourcesToNamespace (
    ACPI_NAMESPACE_NODE     *BufferNode,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;


    /* Get to the ByteData list */

    NextOp = Op->Common.Value.Arg;
    NextOp = NextOp->Common.Next;
    if (!NextOp)
    {
        return;
    }

    /* Set Node and Op to point to each other */

    BufferNode->Op = Op;
    Op->Common.Node = BufferNode;

    /*
     * Insert each resource into the namespace
     * NextOp contains the Aml pointer and the Aml length
     */
    AcpiUtWalkAmlResources (NULL, (UINT8 *) NextOp->Named.Data,
        (ACPI_SIZE) NextOp->Common.Value.Integer,
        AcpiDmAddResourceToNamespace, (void **) BufferNode);
}