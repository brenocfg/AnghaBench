#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int argc; TYPE_1__** argv; } ;
struct TYPE_21__ {char* name; } ;
struct TYPE_20__ {int /*<<< orphan*/  lno; TYPE_4__* frp; TYPE_2__* gp; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* scr_rename ) (TYPE_3__*,char*,int) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  bp; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ FREF ;
typedef  TYPE_5__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  FR_NAMECHANGE ; 
 int FR_TMPEXIT ; 
 int FR_TMPFILE ; 
 int /*<<< orphan*/  F_CLR (TYPE_4__*,int) ; 
 int /*<<< orphan*/  F_ISSET (TYPE_4__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  MSTAT_SHOWLAST ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msgq_status (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_alt_name (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int) ; 
 char* v_strdup (TYPE_3__*,char*,size_t) ; 

int
ex_file(SCR *sp, EXCMD *cmdp)
{
	char *p;
	FREF *frp;
	char *np;
	size_t nlen;

	NEEDFILE(sp, cmdp);

	switch (cmdp->argc) {
	case 0:
		break;
	case 1:
		frp = sp->frp;

		/* Make sure can allocate enough space. */
		INT2CHAR(sp, cmdp->argv[0]->bp, cmdp->argv[0]->len + 1, 
			    np, nlen);
		if ((p = v_strdup(sp, np, nlen - 1)) == NULL)
			return (1);

		/* If already have a file name, it becomes the alternate. */
		if (!F_ISSET(frp, FR_TMPFILE))
			set_alt_name(sp, frp->name);

		/* Free the previous name. */
		free(frp->name);
		frp->name = p;

		/*
		 * The file has a real name, it's no longer a temporary,
		 * clear the temporary file flags.
		 */
		F_CLR(frp, FR_TMPEXIT | FR_TMPFILE);

		/* Have to force a write if the file exists, next time. */
		F_SET(frp, FR_NAMECHANGE);

		/* Notify the screen. */
		(void)sp->gp->scr_rename(sp, sp->frp->name, 1);
		break;
	default:
		abort();
	}
	msgq_status(sp, sp->lno, MSTAT_SHOWLAST);
	return (0);
}