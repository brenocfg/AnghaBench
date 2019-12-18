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
struct TYPE_6__ {TYPE_2__** freeBlocks; } ;
typedef  TYPE_1__ t_MM ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ end; struct TYPE_7__* p_Next; } ;
typedef  TYPE_2__ t_FreeBlock ;
typedef  int /*<<< orphan*/  t_BusyBlock ;

/* Variables and functions */
 int /*<<< orphan*/  AddBusy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateBusyBlock (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ CutFree (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  ILLEGAL_BASE ; 
 scalar_t__ MAKE_ALIGNED (scalar_t__,scalar_t__) ; 
 size_t MM_MAX_ALIGNMENT ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t MmGetGreaterAlignment(t_MM *p_MM, uint64_t size, uint64_t alignment, char* name)
{
    t_FreeBlock *p_FreeB;
    t_BusyBlock *p_NewBusyB;
    uint64_t    holdBase, holdEnd, alignBase = 0;

    /* goes over free blocks of the 64 byte alignment list
       and look for a block of the suitable size and
       base address according to the alignment. */
    p_FreeB = p_MM->freeBlocks[MM_MAX_ALIGNMENT];

    while ( p_FreeB )
    {
        alignBase = MAKE_ALIGNED(p_FreeB->base, alignment);

        /* the block is found if the aligned base inside the block
         * and has the anough size. */
        if ( alignBase >= p_FreeB->base &&
             alignBase < p_FreeB->end &&
             size <= (p_FreeB->end - alignBase) )
            break;
        else
            p_FreeB = p_FreeB->p_Next;
    }

    /* If such block isn't found */
    if ( !p_FreeB )
        return (uint64_t)(ILLEGAL_BASE);

    holdBase = alignBase;
    holdEnd = alignBase + size;

    /* init a new busy block */
    if ((p_NewBusyB = CreateBusyBlock(holdBase, size, name)) == NULL)
        return (uint64_t)(ILLEGAL_BASE);

    /* calls Update routine to update a lists of free blocks */
    if ( CutFree ( p_MM, holdBase, holdEnd ) != E_OK )
    {
        XX_Free(p_NewBusyB);
        return (uint64_t)(ILLEGAL_BASE);
    }

    /* insert the new busy block into the list of busy blocks */
    AddBusy ( p_MM, p_NewBusyB );

    return (holdBase);
}