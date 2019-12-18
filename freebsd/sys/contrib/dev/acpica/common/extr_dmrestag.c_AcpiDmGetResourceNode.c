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
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {scalar_t__ Value; scalar_t__ Length; struct TYPE_4__* Peer; struct TYPE_4__* Child; } ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_DIV_8 (scalar_t__) ; 

__attribute__((used)) static ACPI_NAMESPACE_NODE *
AcpiDmGetResourceNode (
    ACPI_NAMESPACE_NODE     *BufferNode,
    UINT32                  BitIndex)
{
    ACPI_NAMESPACE_NODE     *Node;
    UINT32                  ByteIndex = ACPI_DIV_8 (BitIndex);


    /*
     * Child list contains an entry for each resource descriptor. Find
     * the descriptor that corresponds to the Index.
     *
     * If there are no children, this is not a resource template
     */
    Node = BufferNode->Child;
    while (Node)
    {
        /*
         * Check if the Index falls within this resource.
         *
         * Value contains the resource offset, Object contains the resource
         * length (both in bytes)
         */
        if ((ByteIndex >= Node->Value) &&
            (ByteIndex < (Node->Value + Node->Length)))
        {
            return (Node);
        }

        Node = Node->Peer;
    }

    return (NULL);
}