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
 int POPUNS () ; 
 int /*<<< orphan*/  PUSHUNS (int) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void rshift(FICL_VM *pVM)
{
    FICL_UNS nBits;
    FICL_UNS x1;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,1);
#endif

    nBits = POPUNS();
    x1 = POPUNS();

    PUSHUNS(x1 >> nBits);
    return;
}