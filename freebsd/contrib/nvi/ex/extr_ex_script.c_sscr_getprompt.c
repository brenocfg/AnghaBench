#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  recno_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_15__ {int /*<<< orphan*/  ibcw; } ;
struct TYPE_14__ {TYPE_1__* script; } ;
struct TYPE_13__ {scalar_t__ sh_master; } ;
typedef  TYPE_1__ SCRIPT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EX_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ CHAR2INT5 (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__* EXP (TYPE_2__*) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ db_append (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ db_last (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int read (scalar_t__,char*,size_t) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  sscr_end (TYPE_2__*) ; 
 int sscr_setprompt (TYPE_2__*,char*,size_t) ; 

__attribute__((used)) static int
sscr_getprompt(SCR *sp)
{
	EX_PRIVATE *exp;
	struct timeval tv;
	char *endp, *p, *t, buf[1024];
	SCRIPT *sc;
	fd_set fdset;
	recno_t lline;
	size_t llen, len;
	int nr;
	CHAR_T *wp;
	size_t wlen;

	exp = EXP(sp);

	FD_ZERO(&fdset);
	endp = buf;
	len = sizeof(buf);

	/* Wait up to a second for characters to read. */
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	sc = sp->script;
	FD_SET(sc->sh_master, &fdset);
	switch (select(sc->sh_master + 1, &fdset, NULL, NULL, &tv)) {
	case -1:		/* Error or interrupt. */
		msgq(sp, M_SYSERR, "select");
		goto prompterr;
	case  0:		/* Timeout */
		msgq(sp, M_ERR, "Error: timed out");
		goto prompterr;
	case  1:		/* Characters to read. */
		break;
	}

	/* Read the characters. */
more:	len = sizeof(buf) - (endp - buf);
	switch (nr = read(sc->sh_master, endp, len)) {
	case  0:			/* EOF. */
		msgq(sp, M_ERR, "Error: shell: EOF");
		goto prompterr;
	case -1:			/* Error or interrupt. */
		msgq(sp, M_SYSERR, "shell");
		goto prompterr;
	default:
		endp += nr;
		break;
	}

	/* If any complete lines, push them into the file. */
	for (p = t = buf; p < endp; ++p) {
		if (*p == '\r' || *p == '\n') {
			if (CHAR2INT5(sp, exp->ibcw, t, p - t, wp, wlen))
				goto conv_err;
			if (db_last(sp, &lline) ||
			    db_append(sp, 0, lline, wp, wlen))
				goto prompterr;
			t = p + 1;
		}
	}
	if (p > buf) {
		memmove(buf, t, endp - t);
		endp = buf + (endp - t);
	}
	if (endp == buf)
		goto more;

	/* Wait up 1/10 of a second to make sure that we got it all. */
	tv.tv_sec = 0;
	tv.tv_usec = 100000;
	switch (select(sc->sh_master + 1, &fdset, NULL, NULL, &tv)) {
	case -1:		/* Error or interrupt. */
		msgq(sp, M_SYSERR, "select");
		goto prompterr;
	case  0:		/* Timeout */
		break;
	case  1:		/* Characters to read. */
		goto more;
	}

	/* Timed out, so theoretically we have a prompt. */
	llen = endp - buf;
	endp = buf;

	/* Append the line into the file. */
	if (CHAR2INT5(sp, exp->ibcw, buf, llen, wp, wlen))
		goto conv_err;
	if (db_last(sp, &lline) || db_append(sp, 0, lline, wp, wlen)) {
		if (0)
conv_err:		msgq(sp, M_ERR, "323|Invalid input. Truncated.");
prompterr:	sscr_end(sp);
		return (1);
	}

	return (sscr_setprompt(sp, buf, llen));
}