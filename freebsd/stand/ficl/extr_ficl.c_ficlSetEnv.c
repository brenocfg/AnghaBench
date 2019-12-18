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
struct TYPE_6__ {int /*<<< orphan*/ * envp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * param; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_UNS ;
typedef  TYPE_2__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PSZ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  constantParen ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendWord (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ficlSetEnv(FICL_SYSTEM *pSys, char *name, FICL_UNS value)
{
    STRINGINFO si;
    FICL_WORD *pFW;
    FICL_DICT *envp = pSys->envp;

    SI_PSZ(si, name);
    pFW = dictLookup(envp, si);

    if (pFW == NULL)
    {
        dictAppendWord(envp, name, constantParen, FW_DEFAULT);
        dictAppendCell(envp, LVALUEtoCELL(value));
    }
    else
    {
        pFW->param[0] = LVALUEtoCELL(value);
    }

    return;
}