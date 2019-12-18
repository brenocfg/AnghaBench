#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  base; struct TYPE_4__* p_Next; } ;
typedef  TYPE_1__ t_MemBlock ;
struct TYPE_5__ {TYPE_1__* memBlocks; } ;
typedef  TYPE_2__ t_MM ;
typedef  scalar_t__ t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  ILLEGAL_BASE ; 

uint64_t MM_GetMemBlock(t_Handle h_MM, int index)
{
    t_MM       *p_MM = (t_MM*)h_MM;
    t_MemBlock *p_MemBlock;
    int         i;

    ASSERT_COND(p_MM);

    p_MemBlock = p_MM->memBlocks;
    for (i=0; i < index; i++)
        p_MemBlock = p_MemBlock->p_Next;

    if ( p_MemBlock )
        return (p_MemBlock->base);
    else
        return (uint64_t)ILLEGAL_BASE;
}