#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* smudge; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/ * param; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  TYPE_3__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doDoes ; 
 TYPE_3__* vmGetDict (TYPE_2__*) ; 
 int /*<<< orphan*/  vmPopIP (TYPE_2__*) ; 

__attribute__((used)) static void doesParen(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    dp->smudge->code = doDoes;
    dp->smudge->param[0] = LVALUEtoCELL(pVM->ip);
    vmPopIP(pVM);
    return;
}