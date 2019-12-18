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
struct TYPE_4__ {int /*<<< orphan*/  smudge; } ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmGetDict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recurseCoIm(FICL_VM *pVM)
{
    FICL_DICT *pDict = vmGetDict(pVM);

    IGNORE(pVM);
    dictAppendCell(pDict, LVALUEtoCELL(pDict->smudge));
    return;
}