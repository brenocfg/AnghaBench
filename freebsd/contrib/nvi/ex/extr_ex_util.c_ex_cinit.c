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
typedef  void* recno_t ;
struct TYPE_8__ {int cno; void* lno; } ;
struct TYPE_7__ {int cno; void* lno; } ;
struct TYPE_9__ {int addrcnt; int /*<<< orphan*/  iflags; TYPE_2__ addr2; TYPE_1__ addr1; int /*<<< orphan*/ * cmd; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  argv_init (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * cmds ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
ex_cinit(SCR *sp, EXCMD *cmdp, int cmd_id, int naddr, recno_t lno1, recno_t lno2, int force)
{
	memset(cmdp, 0, sizeof(EXCMD));
	cmdp->cmd = &cmds[cmd_id];
	cmdp->addrcnt = naddr;
	cmdp->addr1.lno = lno1;
	cmdp->addr2.lno = lno2;
	cmdp->addr1.cno = cmdp->addr2.cno = 1;
	if (force)
		cmdp->iflags |= E_C_FORCE;
	(void)argv_init(sp, cmdp);
}