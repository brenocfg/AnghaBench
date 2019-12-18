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
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  int FICL_UNS ;

/* Variables and functions */
 char* POPPTR () ; 
 int POPUNS () ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void move(FICL_VM *pVM)
{
    FICL_UNS u;
    char *addr2;
    char *addr1;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,3,0);
#endif

    u = POPUNS();
    addr2 = POPPTR();
    addr1 = POPPTR();

    if (u == 0) 
        return;
    /*
    ** Do the copy carefully, so as to be
    ** correct even if the two ranges overlap
    */
    if (addr1 >= addr2)
    {
        for (; u > 0; u--)
            *addr2++ = *addr1++;
    }
    else
    {
        addr2 += u-1;
        addr1 += u-1;
        for (; u > 0; u--)
            *addr2-- = *addr1--;
    }

    return;
}