#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int nCells; int /*<<< orphan*/ * pFrame; int /*<<< orphan*/  base; int /*<<< orphan*/  sp; } ;
typedef  TYPE_1__ FICL_STACK ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* ficlMalloc (size_t) ; 

FICL_STACK *stackCreate(unsigned nCells)
{
    size_t size = sizeof (FICL_STACK) + nCells * sizeof (CELL);
    FICL_STACK *pStack = ficlMalloc(size);

#if FICL_ROBUST
    assert (nCells != 0);
    assert (pStack != NULL);
#endif

    pStack->nCells = nCells;
    pStack->sp     = pStack->base;
    pStack->pFrame = NULL;
    return pStack;
}