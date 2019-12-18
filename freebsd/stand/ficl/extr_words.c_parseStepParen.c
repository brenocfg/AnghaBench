#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pStack; TYPE_2__* runningWord; } ;
struct TYPE_8__ {TYPE_1__* param; } ;
struct TYPE_7__ {int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_2__ FICL_WORD ;
typedef  TYPE_3__ FICL_VM ;
typedef  int /*<<< orphan*/  (* FICL_PARSE_STEP ) (TYPE_3__*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void parseStepParen(FICL_VM *pVM)
{
    STRINGINFO si;
    FICL_WORD *pFW = pVM->runningWord;
    FICL_PARSE_STEP pStep = (FICL_PARSE_STEP)(pFW->param->fn);

    SI_SETLEN(si, stackPopINT(pVM->pStack));
    SI_SETPTR(si, stackPopPtr(pVM->pStack));
    
    PUSHINT((*pStep)(pVM, si));

    return;
}