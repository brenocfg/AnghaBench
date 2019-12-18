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
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILE ; 
 int FW_DEFAULT ; 
 int FW_SMUDGE ; 
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  colonParen ; 
 int /*<<< orphan*/  colonTag ; 
 int /*<<< orphan*/ * dictAppendWord2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  markControlTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_1__*) ; 

__attribute__((used)) static void colonNoName(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    FICL_WORD *pFW;
    STRINGINFO si;

    SI_SETLEN(si, 0);
    SI_SETPTR(si, NULL);

    pVM->state = COMPILE;
    pFW = dictAppendWord2(dp, si, colonParen, FW_DEFAULT | FW_SMUDGE);
    PUSHPTR(pFW);
    markControlTag(pVM, colonTag);
    return;
}