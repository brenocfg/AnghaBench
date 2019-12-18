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
struct TYPE_8__ {size_t count; scalar_t__* text; } ;
struct TYPE_7__ {scalar_t__ pad; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_STRING ;
typedef  size_t FICL_COUNT ;

/* Variables and functions */
 scalar_t__ POPINT () ; 
 int /*<<< orphan*/  PUSHPTR (TYPE_2__*) ; 
 int SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int) ; 
 int nPAD ; 
 int /*<<< orphan*/  strcat (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vmParseStringEx (TYPE_1__*,char,int) ; 

__attribute__((used)) static void ficlWord(FICL_VM *pVM)
{
    FICL_STRING *sp;
    char delim;
    STRINGINFO   si;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,1);
#endif

    sp = (FICL_STRING *)pVM->pad;
    delim = (char)POPINT();
    si = vmParseStringEx(pVM, delim, 1);

    if (SI_COUNT(si) > nPAD-1)
        SI_SETLEN(si, nPAD-1);

    sp->count = (FICL_COUNT)SI_COUNT(si);
    strncpy(sp->text, SI_PTR(si), SI_COUNT(si));
    /*#$-GUY CHANGE: I added this.-$#*/
    sp->text[sp->count] = 0;
    strcat(sp->text, " ");

    PUSHPTR(sp);
    return;
}