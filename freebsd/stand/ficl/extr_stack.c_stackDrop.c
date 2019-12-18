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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void stackDrop(FICL_STACK *pStack, int n)
{
#if FICL_ROBUST
    assert(n > 0);
#endif
    pStack->sp -= n;
    return;
}