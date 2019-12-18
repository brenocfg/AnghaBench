#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i; } ;
struct TYPE_7__ {TYPE_2__ sourceID; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_UNS ;
typedef  TYPE_2__ CELL ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE (int /*<<< orphan*/ ) ; 
 char* POPPTR () ; 
 int /*<<< orphan*/  POPUNS () ; 
 int VM_OUTOFTEXT ; 
 int ficlExecC (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmThrow (TYPE_1__*,int) ; 

__attribute__((used)) static void evaluate(FICL_VM *pVM)
{
    FICL_UNS count;
    char *cp;
    CELL id;
    int result;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,0);
#endif

    count = POPUNS();
    cp = POPPTR();

    IGNORE(count);
    id = pVM->sourceID;
    pVM->sourceID.i = -1;
    result = ficlExecC(pVM, cp, count);
    pVM->sourceID = id;
    if (result != VM_OUTOFTEXT)
        vmThrow(pVM, result);

    return;
}