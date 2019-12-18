#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ end; struct TYPE_7__* p_Next; } ;
typedef  TYPE_1__ t_MemBlock ;
struct TYPE_8__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  freeMemSize; TYPE_1__* memBlocks; } ;
typedef  TYPE_2__ t_MM ;
typedef  scalar_t__ t_Handle ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 scalar_t__ AddFree (TYPE_2__*,scalar_t__,scalar_t__) ; 
 TYPE_1__* CreateNewBlock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  E_ALREADY_EXISTS ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

t_Error MM_Add(t_Handle h_MM, uint64_t base, uint64_t size)
{
    t_MM        *p_MM = (t_MM *)h_MM;
    t_MemBlock  *p_MemB, *p_NewMemB;
    t_Error     errCode;
    uint32_t    intFlags;

    ASSERT_COND(p_MM);

    /* find a last block in the list of memory blocks to insert a new
     * memory block
     */
    intFlags = XX_LockIntrSpinlock(p_MM->h_Spinlock);

    p_MemB = p_MM->memBlocks;
    while ( p_MemB->p_Next )
    {
        if ( base >= p_MemB->base && base < p_MemB->end )
        {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
            RETURN_ERROR(MAJOR, E_ALREADY_EXISTS, NO_MSG);
        }
        p_MemB = p_MemB->p_Next;
    }
    /* check for a last memory block */
    if ( base >= p_MemB->base && base < p_MemB->end )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        RETURN_ERROR(MAJOR, E_ALREADY_EXISTS, NO_MSG);
    }

    /* create a new memory block */
    if ((p_NewMemB = CreateNewBlock(base, size)) == NULL)
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
    }

    /* append a new memory block to the end of the list of memory blocks */
    p_MemB->p_Next = p_NewMemB;

    /* add a new free block to the free lists */
    errCode = AddFree(p_MM, base, base+size);
    if (errCode)
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        p_MemB->p_Next = 0;
        XX_Free(p_NewMemB);
        return ((t_Error)errCode);
    }

    /* Adding the new block size to free memory size */
    p_MM->freeMemSize += size;

    XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);

    return (E_OK);
}