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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ base; scalar_t__ end; } ;
typedef  TYPE_1__ t_MemBlock ;
struct TYPE_5__ {TYPE_1__* memBlocks; } ;
typedef  TYPE_2__ t_MM ;
typedef  scalar_t__ t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int FALSE ; 
 int TRUE ; 

bool MM_InRange(t_Handle h_MM, uint64_t addr)
{
    t_MM       *p_MM = (t_MM*)h_MM;
    t_MemBlock *p_MemBlock;

    ASSERT_COND(p_MM);

    p_MemBlock = p_MM->memBlocks;

    if ((addr >= p_MemBlock->base) && (addr < p_MemBlock->end))
        return TRUE;
    else
        return FALSE;
}