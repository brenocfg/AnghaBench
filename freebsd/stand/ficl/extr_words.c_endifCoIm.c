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
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  origTag ; 
 int /*<<< orphan*/  resolveForwardBranch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void endifCoIm(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    resolveForwardBranch(dp, pVM, origTag);
    return;
}