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
struct TYPE_3__ {int /*<<< orphan*/  pStack; int /*<<< orphan*/  rStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  stackGetTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loopICo(FICL_VM *pVM)
{
    CELL index = stackGetTop(pVM->rStack);
    stackPush(pVM->pStack, index);

    return;
}