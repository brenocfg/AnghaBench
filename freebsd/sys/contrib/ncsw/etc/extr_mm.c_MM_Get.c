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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  freeMemSize; TYPE_2__** freeBlocks; } ;
typedef  TYPE_1__ t_MM ;
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {int end; int base; struct TYPE_8__* p_Next; } ;
typedef  TYPE_2__ t_FreeBlock ;
typedef  int /*<<< orphan*/  t_BusyBlock ;

/* Variables and functions */
 int /*<<< orphan*/  AddBusy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateBusyBlock (int,int,char*) ; 
 scalar_t__ CutFree (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  MAJOR ; 
 int MM_MAX_ALIGNMENT ; 
 int MmGetGreaterAlignment (TYPE_1__*,int,int,char*) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t MM_Get(t_Handle h_MM, uint64_t size, uint64_t alignment, char* name)
{
    t_MM        *p_MM = (t_MM *)h_MM;
    t_FreeBlock *p_FreeB;
    t_BusyBlock *p_NewBusyB;
    uint64_t    holdBase, holdEnd, j, i = 0;
    uint32_t    intFlags;

    SANITY_CHECK_RETURN_VALUE(p_MM, E_INVALID_HANDLE, (uint64_t)ILLEGAL_BASE);

    /* checks that alignment value is greater then zero */
    if (alignment == 0)
    {
        alignment = 1;
    }

    j = alignment;

    /* checks if alignment is a power of two, if it correct and if the
       required size is multiple of the given alignment. */
    while ((j & 0x1) == 0)
    {
        i++;
        j = j >> 1;
    }

    /* if the given alignment isn't power of two, returns an error */
    if (j != 1)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("alignment (should be power of 2)"));
        return (uint64_t)ILLEGAL_BASE;
    }

    if (i > MM_MAX_ALIGNMENT)
    {
        return (MmGetGreaterAlignment(p_MM, size, alignment, name));
    }

    intFlags = XX_LockIntrSpinlock(p_MM->h_Spinlock);
    /* look for a block of the size greater or equal to the required size. */
    p_FreeB = p_MM->freeBlocks[i];
    while ( p_FreeB && (p_FreeB->end - p_FreeB->base) < size )
        p_FreeB = p_FreeB->p_Next;

    /* If such block is found */
    if ( !p_FreeB )
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(ILLEGAL_BASE);
    }

    holdBase = p_FreeB->base;
    holdEnd = holdBase + size;

    /* init a new busy block */
    if ((p_NewBusyB = CreateBusyBlock(holdBase, size, name)) == NULL)
    {
        XX_UnlockIntrSpinlock(p_MM->h_Spinlock, intFlags);
        return (uint64_t)(ILLEGAL_BASE);
    }

    /* calls Update routine to update a lists of free blocks */
    if ( CutFree ( p_MM, holdBase, holdEnd ) != E_OK )
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

    return (holdBase);
}