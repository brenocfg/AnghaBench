#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__** freeBlocks; TYPE_3__* busyBlocks; } ;
typedef  TYPE_1__ t_MM ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {struct TYPE_5__* p_Next; int /*<<< orphan*/  end; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ t_FreeBlock ;
struct TYPE_6__ {struct TYPE_6__* p_Next; int /*<<< orphan*/  end; int /*<<< orphan*/  base; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ t_BusyBlock ;

/* Variables and functions */
 int MM_MAX_ALIGNMENT ; 
 int /*<<< orphan*/  XX_Print (char*,...) ; 

void MM_Dump(t_Handle h_MM)
{
    t_MM        *p_MM = (t_MM *)h_MM;
    t_FreeBlock *p_FreeB;
    t_BusyBlock *p_BusyB;
    int          i;

    p_BusyB = p_MM->busyBlocks;
    XX_Print("List of busy blocks:\n");
    while (p_BusyB)
    {
        XX_Print("\t0x%p: (%s: b=0x%llx, e=0x%llx)\n", p_BusyB, p_BusyB->name, p_BusyB->base, p_BusyB->end );
        p_BusyB = p_BusyB->p_Next;
    }

    XX_Print("\nLists of free blocks according to alignment:\n");
    for (i=0; i <= MM_MAX_ALIGNMENT; i++)
    {
        XX_Print("%d alignment:\n", (0x1 << i));
        p_FreeB = p_MM->freeBlocks[i];
        while (p_FreeB)
        {
            XX_Print("\t0x%p: (b=0x%llx, e=0x%llx)\n", p_FreeB, p_FreeB->base, p_FreeB->end);
            p_FreeB = p_FreeB->p_Next;
        }
        XX_Print("\n");
    }
}