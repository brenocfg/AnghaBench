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
struct TYPE_6__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  freeMemSize; TYPE_2__** freeBlocks; } ;
typedef  TYPE_1__ t_MM ;
typedef  scalar_t__ t_Handle ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ end; struct TYPE_7__* p_Next; } ;
typedef  TYPE_2__ t_FreeBlock ;
typedef  int /*<<< orphan*/  t_BusyBlock ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  AddBusy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateBusyBlock (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ CutFree (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ E_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  ILLEGAL_BASE ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t MM_GetForce(t_Handle h_MM, uint64_t base, uint64_t size, char* name)
{
    t_MM        *p_MM = (t_MM *)h_MM;
    t_FreeBlock *p_FreeB;
    t_BusyBlock *p_NewBusyB;
    uint32_t    intFlags;
    bool        blockIsFree = FALSE;

    ASSERT_COND(p_MM);

    intFlags = XX_LockIntrSpinlock(p_MM->h_Spinlock);
    p_FreeB = p_MM->freeBlocks[0]; /* The biggest free blocks are in the
                                      free list with alignment 1 */

    while ( p_FreeB )
    {
        if ( base >= p_FreeB->base && (base+size) <= p_FreeB->end )
        {
            blockIsFree = TRUE;
            break;
        }
        else
            p_FreeB = p_FreeB->p_Next;
    }

    if ( !blockIsFree )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(ILLEGAL_BASE);
    }

    /* init a new busy block */
    if ((p_NewBusyB = CreateBusyBlock(base, size, name)) == NULL)
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(ILLEGAL_BASE);
    }

    /* calls Update routine to update a lists of free blocks */
    if ( CutFree ( p_MM, base, base+size ) != E_OK )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        XX_Free(p_NewBusyB);
        return (uint64_t)(ILLEGAL_BASE);
    }

    /* Decreasing the allocated memory size from free memory size */
    p_MM->freeMemSize -= size;

    /* insert the new busy block into the list of busy blocks */
    AddBusy ( p_MM, p_NewBusyB );
    XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);

    return (base);
}