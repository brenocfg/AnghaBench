#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int here; } ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int dictCellsAvail (TYPE_1__*) ; 
 int dictCellsUsed (TYPE_1__*) ; 

int dictAllotCells(FICL_DICT *pDict, int nCells)
{
#if FICL_ROBUST
    if (nCells > 0)
    {
        if (nCells <= dictCellsAvail(pDict))
            pDict->here += nCells;
        else
            return 1;       /* dict is full */
    }
    else
    {
        nCells = -nCells;
        if (nCells <= dictCellsUsed(pDict))
            pDict->here -= nCells;
        else                /* prevent underflow */
            pDict->here -= dictCellsUsed(pDict);
    }
#else
    pDict->here += nCells;
#endif
    return 0;
}