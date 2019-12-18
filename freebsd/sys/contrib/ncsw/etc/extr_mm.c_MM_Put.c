#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  freeMemSize; TYPE_2__* busyBlocks; } ;
typedef  TYPE_1__ t_MM ;
typedef  scalar_t__ t_Handle ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ end; struct TYPE_7__* p_Next; } ;
typedef  TYPE_2__ t_BusyBlock ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 scalar_t__ AddFree (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t MM_Put(t_Handle h_MM, uint64_t base)
{
    t_MM        *p_MM = (t_MM *)h_MM;
    t_BusyBlock *p_BusyB, *p_PrevBusyB;
    uint64_t    size;
    uint32_t    intFlags;

    ASSERT_COND(p_MM);

    /* Look for a busy block that have the given base value.
     * That block will be returned back to the memory.
     */
    p_PrevBusyB = 0;

    intFlags = XX_LockIntrSpinlock(p_MM->h_Spinlock);
    p_BusyB = p_MM->busyBlocks;
    while ( p_BusyB && base != p_BusyB->base )
    {
        p_PrevBusyB = p_BusyB;
        p_BusyB = p_BusyB->p_Next;
    }

    if ( !p_BusyB )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(0);
    }

    if ( AddFree( p_MM, p_BusyB->base, p_BusyB->end ) != E_OK )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(0);
    }

    /* removes a busy block form the list of busy blocks */
    if ( p_PrevBusyB )
        p_PrevBusyB->p_Next = p_BusyB->p_Next;
    else
        p_MM->busyBlocks = p_BusyB->p_Next;

    size = p_BusyB->end - p_BusyB->base;

    /* Adding the deallocated memory size to free memory size */
    p_MM->freeMemSize += size;

    XX_Free(p_BusyB);
    XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);

    return (size);
}