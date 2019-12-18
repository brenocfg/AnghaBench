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
struct TYPE_7__ {scalar_t__ end; scalar_t__ base; struct TYPE_7__* p_Next; } ;
typedef  TYPE_2__ t_FreeBlock ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 TYPE_2__* CreateFreeBlock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MAKE_ALIGNED (scalar_t__,scalar_t__) ; 
 int MM_MAX_ALIGNMENT ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 

__attribute__((used)) static t_Error AddFree(t_MM *p_MM, uint64_t base, uint64_t end)
{
    t_FreeBlock *p_PrevB, *p_CurrB, *p_NewB;
    uint64_t    alignment;
    uint64_t    alignBase;
    int         i;

    /* Updates free lists to include  a just released block */
    for (i=0; i <= MM_MAX_ALIGNMENT; i++)
    {
        p_PrevB = p_NewB = 0;
        p_CurrB = p_MM->freeBlocks[i];

        alignment = (uint64_t)(0x1 << i);
        alignBase = MAKE_ALIGNED(base, alignment);

        /* Goes to the next free list if there is no block to free */
        if (alignBase >= end)
            continue;

        /* Looks for a free block that should be updated */
        while ( p_CurrB )
        {
            if ( alignBase <= p_CurrB->end )
            {
                if ( end > p_CurrB->end )
                {
                    t_FreeBlock *p_NextB;
                    while ( p_CurrB->p_Next && end > p_CurrB->p_Next->end )
                    {
                        p_NextB = p_CurrB->p_Next;
                        p_CurrB->p_Next = p_CurrB->p_Next->p_Next;
                        XX_Free(p_NextB);
                    }

                    p_NextB = p_CurrB->p_Next;
                    if ( !p_NextB || (p_NextB && end < p_NextB->base) )
                    {
                        p_CurrB->end = end;
                    }
                    else
                    {
                        p_CurrB->end = p_NextB->end;
                        p_CurrB->p_Next = p_NextB->p_Next;
                        XX_Free(p_NextB);
                    }
                }
                else if ( (end < p_CurrB->base) && ((end-alignBase) >= alignment) )
                {
                    if ((p_NewB = CreateFreeBlock(alignBase, end-alignBase)) == NULL)
                        RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);

                    p_NewB->p_Next = p_CurrB;
                    if (p_PrevB)
                        p_PrevB->p_Next = p_NewB;
                    else
                        p_MM->freeBlocks[i] = p_NewB;
                    break;
                }

                if ((alignBase < p_CurrB->base) && (end >= p_CurrB->base))
                {
                    p_CurrB->base = alignBase;
                }

                /* if size of the free block is less then alignment
                 * deletes that free block from the free list. */
                if ( (p_CurrB->end - p_CurrB->base) < alignment)
                {
                    if ( p_PrevB )
                        p_PrevB->p_Next = p_CurrB->p_Next;
                    else
                        p_MM->freeBlocks[i] = p_CurrB->p_Next;
                    XX_Free(p_CurrB);
                    p_CurrB = NULL;
                }
                break;
            }
            else
            {
                p_PrevB = p_CurrB;
                p_CurrB = p_CurrB->p_Next;
            }
        }

        /* If no free block found to be updated, insert a new free block
         * to the end of the free list.
         */
        if ( !p_CurrB && ((((uint64_t)(end-base)) & ((uint64_t)(alignment-1))) == 0) )
        {
            if ((p_NewB = CreateFreeBlock(alignBase, end-base)) == NULL)
                RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);

            if (p_PrevB)
                p_PrevB->p_Next = p_NewB;
            else
                p_MM->freeBlocks[i] = p_NewB;
        }

        /* Update boundaries of the new free block */
        if ((alignment == 1) && !p_NewB)
        {
            if ( p_CurrB && base > p_CurrB->base )
                base = p_CurrB->base;
            if ( p_CurrB && end < p_CurrB->end )
                end = p_CurrB->end;
        }
    }

    return (E_OK);
}