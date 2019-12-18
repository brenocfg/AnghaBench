#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  ficlFree (char*) ; 
 scalar_t__ ficlMalloc (int) ; 
 char* stackPopPtr (int /*<<< orphan*/ ) ; 
 int stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

__attribute__((used)) static void type(FICL_VM *pVM)
{
    FICL_UNS count = stackPopUNS(pVM->pStack);
    char *cp    = stackPopPtr(pVM->pStack);
    char *pDest = (char *)ficlMalloc(count + 1);

    /* 
    ** Since we don't have an output primitive for a counted string
    ** (oops), make sure the string is null terminated. If not, copy
    ** and terminate it.
    */
    if (!pDest)
	vmThrowErr(pVM, "Error: out of memory");
 
    strncpy(pDest, cp, count);
    pDest[count] = '\0';
 
    vmTextOut(pVM, pDest, 0);
 
    ficlFree(pDest);
    return;
}