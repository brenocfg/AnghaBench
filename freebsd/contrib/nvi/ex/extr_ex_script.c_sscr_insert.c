#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_19__ {int /*<<< orphan*/  ibcw; } ;
struct TYPE_18__ {size_t cno; scalar_t__ lno; TYPE_1__* script; } ;
struct TYPE_17__ {scalar_t__ sh_master; } ;
typedef  TYPE_1__ SCRIPT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EX_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ CHAR2INT5 (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__* EXP (TYPE_2__*) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE_SPACE (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_RETC (TYPE_2__*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINREAD ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ db_append (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ db_last (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int read (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  sscr_end (TYPE_2__*) ; 
 int /*<<< orphan*/  sscr_matchprompt (TYPE_2__*,char*,size_t,size_t*) ; 
 scalar_t__ sscr_setprompt (TYPE_2__*,char*,size_t) ; 
 int vs_refresh (TYPE_2__*,int) ; 

__attribute__((used)) static int
sscr_insert(SCR *sp)
{
	EX_PRIVATE *exp;
	struct timeval tv;
	char *endp, *p, *t;
	SCRIPT *sc;
	fd_set rdfd;
	recno_t lno;
	size_t blen, len, tlen;
	int nr, rval;
	char *bp;
	CHAR_T *wp;
	size_t wlen = 0;

	exp = EXP(sp);


	/* Find out where the end of the file is. */
	if (db_last(sp, &lno))
		return (1);

#define	MINREAD	1024
	GET_SPACE_RETC(sp, bp, blen, MINREAD);
	endp = bp;

	/* Read the characters. */
	rval = 1;
	sc = sp->script;
more:	switch (nr = read(sc->sh_master, endp, MINREAD)) {
	case  0:			/* EOF; shell just exited. */
		sscr_end(sp);
		rval = 0;
		goto ret;
	case -1:			/* Error or interrupt. */
		msgq(sp, M_SYSERR, "shell");
		goto ret;
	default:
		endp += nr;
		break;
	}

	/* Append the lines into the file. */
	for (p = t = bp; p < endp; ++p) {
		if (*p == '\r' || *p == '\n') {
			len = p - t;
			if (CHAR2INT5(sp, exp->ibcw, t, len, wp, wlen))
				goto conv_err;
			if (db_append(sp, 1, lno++, wp, wlen))
				goto ret;
			t = p + 1;
		}
	}
	if (p > t) {
		len = p - t;
		/*
		 * If the last thing from the shell isn't another prompt, wait
		 * up to 1/10 of a second for more stuff to show up, so that
		 * we don't break the output into two separate lines.  Don't
		 * want to hang indefinitely because some program is hanging,
		 * confused the shell, or whatever.
		 */
		if (!sscr_matchprompt(sp, t, len, &tlen) || tlen != 0) {
			tv.tv_sec = 0;
			tv.tv_usec = 100000;
			FD_ZERO(&rdfd);
			FD_SET(sc->sh_master, &rdfd);
			if (select(sc->sh_master + 1,
			    &rdfd, NULL, NULL, &tv) == 1) {
				memmove(bp, t, len);
				endp = bp + len;
				goto more;
			}
		}
		if (sscr_setprompt(sp, t, len))
			return (1);
		if (CHAR2INT5(sp, exp->ibcw, t, len, wp, wlen))
			goto conv_err;
		if (db_append(sp, 1, lno++, wp, wlen))
			goto ret;
	}

	/* The cursor moves to EOF. */
	sp->lno = lno;
	sp->cno = wlen ? wlen - 1 : 0;
	rval = vs_refresh(sp, 1);

	if (0)
conv_err:	msgq(sp, M_ERR, "323|Invalid input. Truncated.");

ret:	FREE_SPACE(sp, bp, blen);
	return (rval);
}