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
struct TYPE_4__ {int /*<<< orphan*/ * dp; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_PARSE_STEP ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictAppendWord (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlAddParseStep (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parseStepParen ; 

void ficlAddPrecompiledParseStep(FICL_SYSTEM *pSys, char *name, FICL_PARSE_STEP pStep)
{
    FICL_DICT *dp = pSys->dp;
    FICL_WORD *pFW = dictAppendWord(dp, name, parseStepParen, FW_DEFAULT);
    dictAppendCell(dp, LVALUEtoCELL(pStep));
    ficlAddParseStep(pSys, pFW);
}