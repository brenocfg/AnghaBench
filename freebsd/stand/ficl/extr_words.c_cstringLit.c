#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* text; scalar_t__ count; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; scalar_t__ ip; } ;
typedef  scalar_t__ IPTYPE ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_STRING ;

/* Variables and functions */
 char* alignPtr (char*) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void cstringLit(FICL_VM *pVM)
{
    FICL_STRING *sp = (FICL_STRING *)(pVM->ip);

    char *cp = sp->text;
    cp += sp->count + 1;
    cp = alignPtr(cp);
    pVM->ip = (IPTYPE)(void *)cp;

    stackPushPtr(pVM->pStack, sp);
    return;
}