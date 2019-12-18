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
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  createParen ; 
 int /*<<< orphan*/  dictAllotCells (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dictAppendWord2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictCheckThreshold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmGetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmGetWord (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    STRINGINFO si = vmGetWord(pVM);

    dictCheckThreshold(dp);

    dictAppendWord2(dp, si, createParen, FW_DEFAULT);
    dictAllotCells(dp, 1);
    return;
}