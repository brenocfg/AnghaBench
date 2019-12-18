#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sp; } ;
typedef  TYPE_1__ FICL_STACK ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */

void stackRoll(FICL_STACK *pStack, int n)
{
    CELL c;
    CELL *pCell;

    if (n == 0)
        return;
    else if (n > 0)
    {
        pCell = pStack->sp - n - 1;
        c = *pCell;

        for (;n > 0; --n, pCell++)
        {
            *pCell = pCell[1];
        }

        *pCell = c;
    }
    else
    {
        pCell = pStack->sp - 1;
        c = *pCell;

        for (; n < 0; ++n, pCell--)
        {
            *pCell = pCell[-1];
        }

        *pCell = c;
    }
    return;
}