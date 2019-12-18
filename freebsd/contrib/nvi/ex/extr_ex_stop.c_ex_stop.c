#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  iflags; } ;
struct TYPE_10__ {TYPE_1__* gp; } ;
struct TYPE_9__ {scalar_t__ (* scr_suspend ) (TYPE_2__*,int*) ;} ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOSUSPEND ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_ALL ; 
 int /*<<< orphan*/  ex_emsg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ file_aw (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,int*) ; 

int
ex_stop(SCR *sp, EXCMD *cmdp)
{
	int allowed;

	/* For some strange reason, the force flag turns off autowrite. */
	if (!FL_ISSET(cmdp->iflags, E_C_FORCE) && file_aw(sp, FS_ALL))
		return (1);

	if (sp->gp->scr_suspend(sp, &allowed))
		return (1);
	if (!allowed)
		ex_emsg(sp, NULL, EXM_NOSUSPEND);
	return (0);
}