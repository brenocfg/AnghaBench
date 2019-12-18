#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  iflags; } ;
struct TYPE_10__ {int /*<<< orphan*/ * cargv; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  FREF ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FS_ALL ; 
 int FS_FORCE ; 
 int FS_POSSIBLE ; 
 int FS_SETALT ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  M_ERR ; 
 int SC_FSWITCH ; 
 int SC_STATUS_CNT ; 
 int /*<<< orphan*/ * file_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ file_m1 (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int
ex_rew(SCR *sp, EXCMD *cmdp)
{
	FREF *frp;

	/*
	 * !!!
	 * Historic practice -- you can rewind to the current file.
	 */
	if (sp->argv == NULL) {
		msgq(sp, M_ERR, "113|No previous files to rewind");
		return (1);
	}

	if (file_m1(sp,
	    FL_ISSET(cmdp->iflags, E_C_FORCE), FS_ALL | FS_POSSIBLE))
		return (1);

	/* Switch to the first one. */
	sp->cargv = sp->argv;
	if ((frp = file_add(sp, *sp->cargv)) == NULL)
		return (1);
	if (file_init(sp, frp, NULL, FS_SETALT |
	    (FL_ISSET(cmdp->iflags, E_C_FORCE) ? FS_FORCE : 0)))
		return (1);

	/* Switch and display a file count with the welcome message. */
	F_SET(sp, SC_FSWITCH | SC_STATUS_CNT);

	return (0);
}