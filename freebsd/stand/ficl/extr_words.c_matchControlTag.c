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

/* Variables and functions */
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static void matchControlTag(FICL_VM *pVM, char *tag)
{
    char *cp;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    cp = (char *)stackPopPtr(pVM->pStack);
    /*
    ** Changed the code below to compare the pointers first (by popular demand)
    */
    if ( (cp != tag) && strcmp(cp, tag) )
    {
        vmThrowErr(pVM, "Error -- unmatched control structure \"%s\"", tag);
    }

    return;
}