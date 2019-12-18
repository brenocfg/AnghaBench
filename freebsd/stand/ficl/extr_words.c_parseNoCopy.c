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
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmGetWord0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parseNoCopy(FICL_VM *pVM)
{
    STRINGINFO si;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,0,2);
#endif

    si = vmGetWord0(pVM);
    PUSHPTR(SI_PTR(si));
    PUSHUNS(SI_COUNT(si));
    return;
}