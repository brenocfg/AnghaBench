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
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopUNS (int /*<<< orphan*/ ) ; 
 scalar_t__ tolower (char) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void compareInternal(FICL_VM *pVM, int caseInsensitive)
{
    char *cp1, *cp2;
    FICL_UNS u1, u2, uMin;
    int n = 0;

    vmCheckStack(pVM, 4, 1);
    u2  = stackPopUNS(pVM->pStack);
    cp2 = (char *)stackPopPtr(pVM->pStack);
    u1  = stackPopUNS(pVM->pStack);
    cp1 = (char *)stackPopPtr(pVM->pStack);

    uMin = (u1 < u2)? u1 : u2;
    for ( ; (uMin > 0) && (n == 0); uMin--)
    {
		char c1 = *cp1++;
		char c2 = *cp2++;
		if (caseInsensitive)
		{
			c1 = (char)tolower(c1);
			c2 = (char)tolower(c2);
		}
        n = (int)(c1 - c2);
    }

    if (n == 0)
        n = (int)(u1 - u2);

    if (n < 0) 
        n = -1;
    else if (n > 0)
        n = 1;

    PUSHINT(n);
    return;
}