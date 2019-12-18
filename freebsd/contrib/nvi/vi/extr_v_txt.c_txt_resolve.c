#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  recno_t ;
typedef  int /*<<< orphan*/  VI_PRIVATE ;
struct TYPE_6__ {int /*<<< orphan*/  lno; int /*<<< orphan*/  len; int /*<<< orphan*/  lb; } ;
typedef  int /*<<< orphan*/  TEXTH ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINE_RESET ; 
 int /*<<< orphan*/  SC_TINPUT ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXT_AUTOINDENT ; 
 int /*<<< orphan*/ * VIP (int /*<<< orphan*/ *) ; 
 scalar_t__ db_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ db_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  txt_ai_resolve (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 scalar_t__ vs_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_resolve(SCR *sp, TEXTH *tiqh, u_int32_t flags)
{
	VI_PRIVATE *vip;
	TEXT *tp;
	recno_t lno;
	int changed;

	/*
	 * The first line replaces a current line, and all subsequent lines
	 * are appended into the file.  Resolve autoindented characters for
	 * each line before committing it.  If the latter causes the line to
	 * change, we have to redisplay it, otherwise the information cached
	 * about the line will be wrong.
	 */
	vip = VIP(sp);
	tp = TAILQ_FIRST(tiqh);

	if (LF_ISSET(TXT_AUTOINDENT))
		txt_ai_resolve(sp, tp, &changed);
	else
		changed = 0;
	if (db_set(sp, tp->lno, tp->lb, tp->len) ||
	    (changed && vs_change(sp, tp->lno, LINE_RESET)))
		return (1);

	for (lno = tp->lno; (tp = TAILQ_NEXT(tp, q)) != NULL; ++lno) {
		if (LF_ISSET(TXT_AUTOINDENT))
			txt_ai_resolve(sp, tp, &changed);
		else
			changed = 0;
		if (db_append(sp, 0, lno, tp->lb, tp->len) ||
		    (changed && vs_change(sp, tp->lno, LINE_RESET)))
			return (1);
	}

	/*
	 * Clear the input flag, the look-aside buffer is no longer valid.
	 * Has to be done as part of text resolution, or upon return we'll
	 * be looking at incorrect data.
	 */
	F_CLR(sp, SC_TINPUT);

	return (0);
}