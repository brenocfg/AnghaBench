#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  bp; } ;
struct TYPE_4__ {int /*<<< orphan*/  iflags; TYPE_2__** argv; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  FREF ;
typedef  TYPE_1__ EXCMD ;
typedef  TYPE_2__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FR_RECOVER ; 
 int FS_FORCE ; 
 int FS_SETALT ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  SC_FSWITCH ; 
 int /*<<< orphan*/ * file_add (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ file_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ file_m2 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_alt_name (int /*<<< orphan*/ *,char*) ; 

int
ex_recover(SCR *sp, EXCMD *cmdp)
{
	ARGS *ap;
	FREF *frp;
	char *np;
	size_t nlen;

	ap = cmdp->argv[0];

	/* Set the alternate file name. */
	INT2CHAR(sp, ap->bp, ap->len+1, np, nlen);
	set_alt_name(sp, np);

	/*
	 * Check for modifications.  Autowrite did not historically
	 * affect :recover.
	 */
	if (file_m2(sp, FL_ISSET(cmdp->iflags, E_C_FORCE)))
		return (1);

	/* Get a file structure for the file. */
	INT2CHAR(sp, ap->bp, ap->len+1, np, nlen);
	if ((frp = file_add(sp, np)) == NULL)
		return (1);

	/* Set the recover bit. */
	F_SET(frp, FR_RECOVER);

	/* Switch files. */
	if (file_init(sp, frp, NULL, FS_SETALT |
	    (FL_ISSET(cmdp->iflags, E_C_FORCE) ? FS_FORCE : 0)))
		return (1);

	F_SET(sp, SC_FSWITCH);
	return (0);
}