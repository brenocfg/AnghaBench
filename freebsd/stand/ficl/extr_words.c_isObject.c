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
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_FALSE ; 
 int /*<<< orphan*/  FICL_TRUE ; 
 int FW_ISOBJECT ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isObject(FICL_VM *pVM)
{
    FICL_INT flag;
    FICL_WORD *pFW = (FICL_WORD *)stackPopPtr(pVM->pStack);
    
    flag = ((pFW != NULL) && (pFW->flags & FW_ISOBJECT)) ? FICL_TRUE : FICL_FALSE;
    stackPushINT(pVM->pStack, flag);
    return;
}