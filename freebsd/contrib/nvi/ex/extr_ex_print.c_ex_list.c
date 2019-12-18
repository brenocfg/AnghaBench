#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_9__ {int iflags; TYPE_5__ addr2; int /*<<< orphan*/  addr1; } ;
struct TYPE_8__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int E_C_LIST ; 
 scalar_t__ ex_print (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 

int
ex_list(SCR *sp, EXCMD *cmdp)
{
	if (ex_print(sp, cmdp,
	    &cmdp->addr1, &cmdp->addr2, cmdp->iflags | E_C_LIST))
		return (1);
	sp->lno = cmdp->addr2.lno;
	sp->cno = cmdp->addr2.cno;
	return (0);
}