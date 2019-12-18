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
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlParseWord (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lookup(FICL_VM *pVM)
{
    STRINGINFO si;
    SI_SETLEN(si, stackPopUNS(pVM->pStack));
    SI_SETPTR(si, stackPopPtr(pVM->pStack));
    stackPushINT(pVM->pStack, ficlParseWord(pVM, si));
    return;
}