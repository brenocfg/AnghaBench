#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_3__ {int BufferLength; void* Buffer; } ;
typedef  TYPE_1__ ASL_RESOURCE_NODE ;

/* Variables and functions */
 void* UtLocalCalloc (int) ; 

ASL_RESOURCE_NODE *
RsAllocateResourceNode (
    UINT32                  Size)
{
    ASL_RESOURCE_NODE       *Rnode;


    /* Allocate the node */

    Rnode = UtLocalCalloc (sizeof (ASL_RESOURCE_NODE));

    /* Allocate the resource descriptor itself */

    Rnode->Buffer = UtLocalCalloc (Size);
    Rnode->BufferLength = Size;
    return (Rnode);
}