#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_30__ {size_t len; int /*<<< orphan*/ * bp; } ;
struct TYPE_29__ {int argc; TYPE_5__** argv; } ;
struct TYPE_28__ {TYPE_1__* gp; } ;
struct TYPE_27__ {int cno; scalar_t__ owrite; scalar_t__ len; int /*<<< orphan*/  insert; int /*<<< orphan*/ * lb; int /*<<< orphan*/  lb_len; int /*<<< orphan*/  offset; int /*<<< orphan*/  ai; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* scr_bell ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ TEXT ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;
typedef  TYPE_5__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETW (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FREE_SPACEW (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_3__*,int /*<<< orphan*/ *,int,char*,size_t) ; 
 scalar_t__ IS_ESCAPE (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 size_t MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OOBLNO ; 
 size_t STRLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * argv_esc (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  argv_flt_ex (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ argv_flt_path (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * argv_uesc (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ cmdskip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_cinit (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* expanduser (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  txt_fc_col (TYPE_3__*,int,TYPE_5__**) ; 

__attribute__((used)) static int
txt_fc(SCR *sp, TEXT *tp, int *redrawp)
{
	struct stat sb;
	ARGS **argv;
	EXCMD cmd;
	size_t indx, len, nlen, off;
	int argc;
	CHAR_T *p, *t, *bp;
	char *np, *epd = NULL;
	size_t nplen;
	int fstwd = 1;

	*redrawp = 0;
	ex_cinit(sp, &cmd, 0, 0, OOBLNO, OOBLNO, 0);

	/*
	 * Find the beginning of this "word" -- if we're at the beginning
	 * of the line, it's a special case.
	 */
	if (tp->cno == 1) {
		len = 0;
		p = tp->lb;
	} else {
		CHAR_T *ap;

		for (len = 0,
		    off = MAX(tp->ai, tp->offset), ap = tp->lb + off, p = ap;
		    off < tp->cno; ++off, ++ap) {
			if (IS_ESCAPE(sp, &cmd, *ap)) {
				if (++off == tp->cno)
					break;
				++ap;
				len += 2;
			} else if (cmdskip(*ap)) {
				p = ap + 1;
				if (len > 0)
					fstwd = 0;
				len = 0;
			} else
				++len;
		}
	}

	/*
	 * If we are at the first word, do ex command completion instead of
	 * file name completion.
	 */
	if (fstwd)
		(void)argv_flt_ex(sp, &cmd, p, len);
	else {
		if ((bp = argv_uesc(sp, &cmd, p, len)) == NULL)
			return (1);
		if (argv_flt_path(sp, &cmd, bp, STRLEN(bp))) {
			FREE_SPACEW(sp, bp, 0);
			return (0);
		}
		FREE_SPACEW(sp, bp, 0);
	}
	argc = cmd.argc;
	argv = cmd.argv;

	switch (argc) {
	case 0:				/* No matches. */
		(void)sp->gp->scr_bell(sp);
		return (0);
	case 1:				/* One match. */
		/* Always overwrite the old text. */
		nlen = STRLEN(cmd.argv[0]->bp);
		break;
	default:			/* Multiple matches. */
		*redrawp = 1;
		if (txt_fc_col(sp, argc, argv))
			return (1);

		/* Find the length of the shortest match. */
		for (nlen = cmd.argv[0]->len; --argc > 0;) {
			if (cmd.argv[argc]->len < nlen)
				nlen = cmd.argv[argc]->len;
			for (indx = 0; indx < nlen &&
			    cmd.argv[argc]->bp[indx] == cmd.argv[0]->bp[indx];
			    ++indx);
			nlen = indx;
		}
		break;
	}

	/* Escape the matched part of the path. */
	if (fstwd)
		bp = cmd.argv[0]->bp;
	else {
		if ((bp = argv_esc(sp, &cmd, cmd.argv[0]->bp, nlen)) == NULL)
			return (1);
		nlen = STRLEN(bp);
	}

	/* Overwrite the expanded text first. */
	for (t = bp; len > 0 && nlen > 0; --len, --nlen)
		*p++ = *t++;

	/* If lost text, make the remaining old text overwrite characters. */
	if (len) {
		tp->cno -= len;
		tp->owrite += len;
	}

	/* Overwrite any overwrite characters next. */
	for (; nlen > 0 && tp->owrite > 0; --nlen, --tp->owrite, ++tp->cno)
		*p++ = *t++;

	/* Shift remaining text up, and move the cursor to the end. */
	if (nlen) {
		off = p - tp->lb;
		BINC_RETW(sp, tp->lb, tp->lb_len, tp->len + nlen);
		p = tp->lb + off;

		tp->cno += nlen;
		tp->len += nlen;

		if (tp->insert != 0)
			(void)MEMMOVE(p + nlen, p, tp->insert);
		while (nlen--)
			*p++ = *t++;
	}

	if (!fstwd)
		FREE_SPACEW(sp, bp, 0);

	/* If not a single match of path, we've done. */
	if (argc != 1 || fstwd)
		return (0);

	/* If a single match and it's a directory, append a '/'. */
	INT2CHAR(sp, cmd.argv[0]->bp, cmd.argv[0]->len + 1, np, nplen);
	if ((epd = expanduser(np)) != NULL)
		np = epd;
	if (!stat(np, &sb) && S_ISDIR(sb.st_mode)) {
		if (tp->owrite == 0) {
			off = p - tp->lb;
			BINC_RETW(sp, tp->lb, tp->lb_len, tp->len + 1);
			p = tp->lb + off;
			if (tp->insert != 0)
				(void)MEMMOVE(p + 1, p, tp->insert);
			++tp->len;
		} else
			--tp->owrite;

		++tp->cno;
		*p++ = '/';
	}
	free(epd);
	return (0);
}