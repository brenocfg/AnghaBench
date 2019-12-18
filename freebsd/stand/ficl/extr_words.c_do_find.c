#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  void FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int) ; 
 int /*<<< orphan*/  PUSHPTR (void*) ; 
 int /*<<< orphan*/  PUSHUNS (int /*<<< orphan*/ ) ; 
 void* dictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmGetDict (int /*<<< orphan*/ *) ; 
 scalar_t__ wordIsImmediate (void*) ; 

__attribute__((used)) static void do_find(FICL_VM *pVM, STRINGINFO si, void *returnForFailure)
{
    FICL_WORD *pFW;

    pFW = dictLookup(vmGetDict(pVM), si);
    if (pFW)
    {
        PUSHPTR(pFW);
        PUSHINT((wordIsImmediate(pFW) ? 1 : -1));
    }
    else
    {
        PUSHPTR(returnForFailure);
        PUSHUNS(0);
    }
    return;
}