#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  iflags; TYPE_1__** argv; } ;
struct TYPE_19__ {struct TYPE_19__* nextdisp; int /*<<< orphan*/  argv; int /*<<< orphan*/  cargv; int /*<<< orphan*/  gp; } ;
struct TYPE_18__ {scalar_t__ len; int /*<<< orphan*/  bp; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  FREF ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FORCE ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  SC_SSWITCH ; 
 int /*<<< orphan*/  SC_STATUS_CNT ; 
 int /*<<< orphan*/  ex_buildargv (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_add (TYPE_2__*,char*) ; 
 scalar_t__ file_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_end (TYPE_2__*) ; 
 scalar_t__ screen_init (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  vs_discard (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vs_split (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ex_N_next(SCR *sp, EXCMD *cmdp)
{
	SCR *new;
	FREF *frp;
	char *np;
	size_t nlen;

	/* Get a new screen. */
	if (screen_init(sp->gp, sp, &new))
		return (1);
	if (vs_split(sp, new, 0)) {
		(void)screen_end(new);
		return (1);
	}

	/* Get a backing file. */
	INT2CHAR(sp, cmdp->argv[0]->bp, cmdp->argv[0]->len + 1, np, nlen);
	if ((frp = file_add(new, np)) == NULL ||
	    file_init(new, frp, NULL,
	    (FL_ISSET(cmdp->iflags, E_C_FORCE) ? FS_FORCE : 0))) {
		(void)vs_discard(new, NULL);
		(void)screen_end(new);
		return (1);
	}

	/* The arguments are a replacement file list. */
	new->cargv = new->argv = ex_buildargv(sp, cmdp, NULL);

	/* Display a file count with the welcome message. */
	F_SET(new, SC_STATUS_CNT);

	/* Set up the switch. */
	sp->nextdisp = new;
	F_SET(sp, SC_SSWITCH);

	return (0);
}