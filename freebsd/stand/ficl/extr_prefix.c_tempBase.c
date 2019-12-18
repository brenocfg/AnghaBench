#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int base; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlParseNumber (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmGetWord0 (TYPE_1__*) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tempBase(FICL_VM *pVM, int base)
{
    int oldbase = pVM->base;
    STRINGINFO si = vmGetWord0(pVM);

    pVM->base = base;
    if (!ficlParseNumber(pVM, si)) 
    {
        int i = SI_COUNT(si);
        vmThrowErr(pVM, "%.*s not recognized", i, SI_PTR(si));
    }

    pVM->base = oldbase;
    return;
}