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
struct TYPE_4__ {scalar_t__ BufferLength; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ASL_RESOURCE_NODE ;

/* Variables and functions */

UINT32
RsLinkDescriptorChain (
    ASL_RESOURCE_NODE       **PreviousRnode,
    ASL_RESOURCE_NODE       *Rnode)
{
    ASL_RESOURCE_NODE       *LastRnode;
    UINT32                  CurrentByteOffset;


    /* Anything to do? */

    if (!Rnode)
    {
        return (0);
    }

    /* Point the previous node to the new node */

    (*PreviousRnode)->Next = Rnode;
    CurrentByteOffset = Rnode->BufferLength;

    /* Walk to the end of the chain headed by Rnode */

    LastRnode = Rnode;
    while (LastRnode->Next)
    {
        LastRnode = LastRnode->Next;
        CurrentByteOffset += LastRnode->BufferLength;
    }

    /* Previous node becomes the last node in the chain */

    *PreviousRnode = LastRnode;
    return (CurrentByteOffset);
}