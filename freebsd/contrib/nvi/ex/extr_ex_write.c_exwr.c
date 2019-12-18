#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_13__ ;
typedef  struct TYPE_37__   TYPE_12__ ;

/* Type definitions */
typedef  enum which { ____Placeholder_which } which ;
struct TYPE_38__ {scalar_t__ lno; } ;
struct TYPE_37__ {int lno; } ;
struct TYPE_44__ {int argc; TYPE_13__ addr2; TYPE_12__ addr1; TYPE_2__** argv; TYPE_1__* cmd; int /*<<< orphan*/  iflags; } ;
struct TYPE_43__ {char* lastbcomm; } ;
struct TYPE_42__ {char* name; struct TYPE_42__* frp; TYPE_3__* gp; } ;
struct TYPE_41__ {int /*<<< orphan*/  (* scr_rename ) (TYPE_4__*,char*,int) ;} ;
struct TYPE_40__ {char* bp; int /*<<< orphan*/  len; } ;
struct TYPE_39__ {char* usage; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ SCR ;
typedef  int /*<<< orphan*/  MARK ;
typedef  TYPE_5__ EX_PRIVATE ;
typedef  TYPE_6__ EXCMD ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_FILECOUNT ; 
 int /*<<< orphan*/  EXM_SECURE_F ; 
 int /*<<< orphan*/  EXM_USAGE ; 
 TYPE_5__* EXP (TYPE_4__*) ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FILTER_WRITE ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FR_EXNAMED ; 
 int FR_NAMECHANGE ; 
 int FR_TMPEXIT ; 
 int FR_TMPFILE ; 
 int /*<<< orphan*/  FS_ALL ; 
 int /*<<< orphan*/  FS_APPEND ; 
 int /*<<< orphan*/  FS_FORCE ; 
 int /*<<< orphan*/  FS_POSSIBLE ; 
 int /*<<< orphan*/  F_CLR (TYPE_4__*,int) ; 
 scalar_t__ F_ISSET (TYPE_4__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_4__*,int) ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_4__*,char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  LF_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ O_ISSET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_SECURE ; 
 int SC_EX_SILENT ; 
 int SC_EX_WAIT_YES ; 
 int SC_VI ; 
 int /*<<< orphan*/  STRLEN (char*) ; 
 int WRITE ; 
 int XIT ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ argv_exp1 (TYPE_4__*,TYPE_6__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ argv_exp2 (TYPE_4__*,TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cmdskip (char) ; 
 int /*<<< orphan*/  db_exist (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ex_emsg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_filter (TYPE_4__*,TYPE_6__*,TYPE_12__*,TYPE_13__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_puts (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ex_wemsg (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int file_write (TYPE_4__*,TYPE_12__*,TYPE_13__*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  set_alt_name (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*,int) ; 
 char* v_strdup (TYPE_4__*,char*,size_t) ; 
 char* v_wstrdup (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exwr(SCR *sp, EXCMD *cmdp, enum which cmd)
{
	MARK rm;
	int flags;
	char *name;
	CHAR_T *p = NULL;
	size_t nlen;
	char *n;
	int rc;
	EX_PRIVATE *exp;

	NEEDFILE(sp, cmdp);

	/* All write commands can have an associated '!'. */
	LF_INIT(FS_POSSIBLE);
	if (FL_ISSET(cmdp->iflags, E_C_FORCE))
		LF_SET(FS_FORCE);

	/* Skip any leading whitespace. */
	if (cmdp->argc != 0)
		for (p = cmdp->argv[0]->bp; *p != '\0' && cmdskip(*p); ++p);

	/* If "write !" it's a pipe to a utility. */
	if (cmdp->argc != 0 && cmd == WRITE && *p == '!') {
		/* Secure means no shell access. */
		if (O_ISSET(sp, O_SECURE)) {
			ex_wemsg(sp, cmdp->cmd->name, EXM_SECURE_F);
			return (1);
		}

		/* Expand the argument. */
		for (++p; *p && cmdskip(*p); ++p);
		if (*p == '\0') {
			ex_emsg(sp, cmdp->cmd->usage, EXM_USAGE);
			return (1);
		}
		if (argv_exp1(sp, cmdp, p, STRLEN(p), 1))
			return (1);

		/* Set the last bang command */
		exp = EXP(sp);
		free(exp->lastbcomm);
		exp->lastbcomm = v_wstrdup(sp, cmdp->argv[1]->bp,
		    cmdp->argv[1]->len);

		/*
		 * Historically, vi waited after a write filter even if there
		 * wasn't any output from the command.  People complained when
		 * nvi waited only if there was output, wanting the visual cue
		 * that the program hadn't written anything.
		 */
		F_SET(sp, SC_EX_WAIT_YES);

		/*
		 * !!!
		 * Ignore the return cursor position, the cursor doesn't
		 * move.
		 */
		if (ex_filter(sp, cmdp, &cmdp->addr1,
		    &cmdp->addr2, &rm, cmdp->argv[1]->bp, FILTER_WRITE))
			return (1);

		/* Ex terminates with a bang, even if the command fails. */
		if (!F_ISSET(sp, SC_VI) && !F_ISSET(sp, SC_EX_SILENT))
			(void)ex_puts(sp, "!\n");

		return (0);
	}

	/* Set the FS_ALL flag if we're writing the entire file. */
	if (cmdp->addr1.lno <= 1 && !db_exist(sp, cmdp->addr2.lno + 1))
		LF_SET(FS_ALL);

	/* If "write >>" it's an append to a file. */
	if (cmdp->argc != 0 && cmd != XIT && p[0] == '>' && p[1] == '>') {
		LF_SET(FS_APPEND);

		/* Skip ">>" and whitespace. */
		for (p += 2; *p && cmdskip(*p); ++p);
	}

	/* If no other arguments, just write the file back. */
	if (cmdp->argc == 0 || *p == '\0')
		return (file_write(sp,
		    &cmdp->addr1, &cmdp->addr2, NULL, flags));

	/* Build an argv so we get an argument count and file expansion. */
	if (argv_exp2(sp, cmdp, p, STRLEN(p)))
		return (1);

	/*
	 *  0 args: impossible.
	 *  1 args: impossible (I hope).
	 *  2 args: read it.
	 * >2 args: object, too many args.
	 *
	 * The 1 args case depends on the argv_sexp() function refusing
	 * to return success without at least one non-blank character.
	 */
	switch (cmdp->argc) {
	case 0:
	case 1:
		abort();
		/* NOTREACHED */
	case 2:
		INT2CHAR(sp, cmdp->argv[1]->bp, cmdp->argv[1]->len+1,
			 n, nlen);
		name = v_strdup(sp, n, nlen - 1);

		/*
		 * !!!
		 * Historically, the read and write commands renamed
		 * "unnamed" files, or, if the file had a name, set
		 * the alternate file name.
		 */
		if (F_ISSET(sp->frp, FR_TMPFILE) &&
		    !F_ISSET(sp->frp, FR_EXNAMED)) {
			if ((n = v_strdup(sp, name, nlen - 1)) != NULL) {
				free(sp->frp->name);
				sp->frp->name = n;
			}
			/*
			 * The file has a real name, it's no longer a
			 * temporary, clear the temporary file flags.
			 *
			 * !!!
			 * If we're writing the whole file, FR_NAMECHANGE
			 * will be cleared by the write routine -- this is
			 * historic practice.
			 */
			F_CLR(sp->frp, FR_TMPEXIT | FR_TMPFILE);
			F_SET(sp->frp, FR_NAMECHANGE | FR_EXNAMED);

			/* Notify the screen. */
			(void)sp->gp->scr_rename(sp, sp->frp->name, 1);
		} else
			set_alt_name(sp, name);
		break;
	default:
		INT2CHAR(sp, p, STRLEN(p) + 1, n, nlen);
		ex_emsg(sp, n, EXM_FILECOUNT);
		return (1);
	}

	rc = file_write(sp, &cmdp->addr1, &cmdp->addr2, name, flags);

	free(name);

	return rc;
}