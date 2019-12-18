#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int recno_t ;
struct TYPE_13__ {int lno; } ;
struct TYPE_12__ {int /*<<< orphan*/ * gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ MARK ;
typedef  int /*<<< orphan*/  GS ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  E_C_HASH ; 
 int /*<<< orphan*/  E_C_LIST ; 
 scalar_t__ INTERRUPTED (TYPE_1__*) ; 
 int /*<<< orphan*/ * L (char*) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ db_get (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ex_ldisplay (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_prchars (TYPE_1__*,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_puts (TYPE_1__*,char*) ; 

int
ex_print(SCR *sp, EXCMD *cmdp, MARK *fp, MARK *tp, u_int32_t flags)
{
	GS *gp;
	recno_t from, to;
	size_t col, len;
	CHAR_T *p;
	CHAR_T buf[10];

	NEEDFILE(sp, cmdp);

	gp = sp->gp;
	for (from = fp->lno, to = tp->lno; from <= to; ++from) {
		col = 0;

		/*
		 * Display the line number.  The %6 format is specified
		 * by POSIX 1003.2, and is almost certainly large enough.
		 * Check, though, just in case.
		 */
		if (LF_ISSET(E_C_HASH)) {
			if (from <= 999999) {
				SPRINTF(buf, SIZE(buf), L("%6u  "), from);
				p = buf;
			} else
				p = L("TOOBIG  ");
			if (ex_prchars(sp, p, &col, 8, 0, 0))
				return (1);
		}

		/*
		 * Display the line.  The format for E_C_PRINT isn't very good,
		 * especially in handling end-of-line tabs, but they're almost
		 * backward compatible.
		 */
		if (db_get(sp, from, DBG_FATAL, &p, &len))
			return (1);

		if (len == 0 && !LF_ISSET(E_C_LIST))
			(void)ex_puts(sp, "\n");
		else if (ex_ldisplay(sp, p, len, col, flags))
			return (1);

		if (INTERRUPTED(sp))
			break;
	}
	return (0);
}