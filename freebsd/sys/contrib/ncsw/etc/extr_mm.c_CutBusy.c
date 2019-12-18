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
struct TYPE_6__ {TYPE_2__* busyBlocks; } ;
typedef  TYPE_1__ t_MM ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {scalar_t__ end; scalar_t__ base; struct TYPE_7__* p_Next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ t_BusyBlock ;

/* Variables and functions */
 TYPE_2__* CreateBusyBlock (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 

__attribute__((used)) static t_Error CutBusy(t_MM *p_MM, uint64_t base, uint64_t end)
{
    t_BusyBlock  *p_CurrB, *p_PrevB, *p_NewB;

    p_CurrB = p_MM->busyBlocks;
    p_PrevB = p_NewB = 0;

    while ( p_CurrB )
    {
        if ( base < p_CurrB->end )
        {
            if ( end > p_CurrB->end )
            {
                t_BusyBlock *p_NextB;
                while ( p_CurrB->p_Next && end >= p_CurrB->p_Next->end )
                {
                    p_NextB = p_CurrB->p_Next;
                    p_CurrB->p_Next = p_CurrB->p_Next->p_Next;
                    XX_Free(p_NextB);
                }

                p_NextB = p_CurrB->p_Next;
                if ( p_NextB && end > p_NextB->base )
                {
                    p_NextB->base = end;
                }
            }

            if ( base <= p_CurrB->base )
            {
                if ( end < p_CurrB->end && end > p_CurrB->base )
                {
                    p_CurrB->base = end;
                }
                else if ( end >= p_CurrB->end )
                {
                    if ( p_PrevB )
                        p_PrevB->p_Next = p_CurrB->p_Next;
                    else
                        p_MM->busyBlocks = p_CurrB->p_Next;
                    XX_Free(p_CurrB);
                }
            }
            else
            {
                if ( end < p_CurrB->end && end > p_CurrB->base )
                {
                    if ((p_NewB = CreateBusyBlock(end,
                                                  p_CurrB->end-end,
                                                  p_CurrB->name)) == NULL)
                        RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
                    p_NewB->p_Next = p_CurrB->p_Next;
                    p_CurrB->p_Next = p_NewB;
                }
                p_CurrB->end = base;
            }
            break;
        }
        else
        {
            p_PrevB = p_CurrB;
            p_CurrB = p_CurrB->p_Next;
        }
    }

    return (E_OK);
}