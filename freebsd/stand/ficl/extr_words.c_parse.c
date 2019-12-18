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
 scalar_t__ POPINT () ; 
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vmParseStringEx (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse(FICL_VM *pVM)
{
    STRINGINFO si;
    char delim;

#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,2);
#endif

    delim = (char)POPINT();

    si = vmParseStringEx(pVM, delim, 0);
    PUSHPTR(SI_PTR(si));
    PUSHUNS(SI_COUNT(si));
    return;
}