#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ p; } ;
struct TYPE_9__ {TYPE_1__* runningWord; } ;
struct TYPE_8__ {TYPE_3__* param; } ;
typedef  scalar_t__ IPTYPE ;
typedef  TYPE_2__ FICL_VM ;
typedef  TYPE_3__ CELL ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHPTR (TYPE_3__*) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmPushIP (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void doDoes(FICL_VM *pVM)
{
    CELL *pCell;
    IPTYPE tempIP;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 0, 1);
#endif

    pCell = pVM->runningWord->param;
    tempIP = (IPTYPE)((*pCell).p);
    PUSHPTR(pCell+1);
    vmPushIP(pVM, tempIP);
    return;
}