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
struct TYPE_3__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
typedef  int /*<<< orphan*/  FICL_STACK ;
typedef  TYPE_1__ DPUNS ;

/* Variables and functions */
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void  u64Push(FICL_STACK *pStack, DPUNS u64)
{
    stackPushINT(pStack, u64.lo);
    stackPushINT(pStack, u64.hi);
    return;
}