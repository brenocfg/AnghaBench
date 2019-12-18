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

__attribute__((used)) static t_Error CutFree(t_MM *p_MM, uint64_t holdBase, uint64_t holdEnd)
{
    t_FreeBlock *p_PrevB, *p_CurrB, *p_NewB;
    uint64_t    alignBase, base, end;
    uint64_t    alignment;
    int         i;

    for (i=0; i <= MM_MAX_ALIGNMENT; i++)
    {
        p_PrevB = p_NewB = 0;
        p_CurrB = p_MM->freeBlocks[i];

        alignment = (uint64_t)(0x1 << i);
        alignBase = MAKE_ALIGNED(holdEnd, alignment);

        while ( p_CurrB )
        {
            base = p_CurrB->base;
            end = p_CurrB->end;

            if ( (holdBase <= base) && (holdEnd <= end) && (holdEnd > base) )
            {
                if ( alignBase >= end ||
                     (alignBase < end && ((end-alignBase) < alignment)) )
                {
                    if (p_PrevB)
                        p_PrevB->p_Next = p_CurrB->p_Next;
                    else
                        p_MM->freeBlocks[i] = p_CurrB->p_Next;
                    XX_Free(p_CurrB);
                }
                else
                {
                    p_CurrB->base = alignBase;
                }
                break;
            }
            else if ( (holdBase > base) && (holdEnd <= end) )
            {
                if ( (holdBase-base) >= alignment )
                {
                    if ( (alignBase < end) && ((end-alignBase) >= alignment) )
                    {
                        if ((p_NewB = CreateFreeBlock(alignBase, end-alignBase)) == NULL)
                            RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
                        p_NewB->p_Next = p_CurrB->p_Next;
                        p_CurrB->p_Next = p_NewB;
                    }
                    p_CurrB->end = holdBase;
                }
                else if ( (alignBase < end) && ((end-alignBase) >= alignment) )
                {
                    p_CurrB->base = alignBase;
                }
                else
                {
                    if (p_PrevB)
                        p_PrevB->p_Next = p_CurrB->p_Next;
                    else
                        p_MM->freeBlocks[i] = p_CurrB->p_Next;
                    XX_Free(p_CurrB);
                }
                break;
            }
            else
            {
                p_PrevB = p_CurrB;
                p_CurrB = p_CurrB->p_Next;
            }
        }
    }

    return (E_OK);
}