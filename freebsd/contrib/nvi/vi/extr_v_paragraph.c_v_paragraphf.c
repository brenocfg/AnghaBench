#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_8__ {size_t cno; int lno; } ;
struct TYPE_9__ {int count; TYPE_1__ m_stop; TYPE_1__ m_start; TYPE_1__ m_final; int /*<<< orphan*/  rkp; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEXT_CHECK ; 
 scalar_t__ ISCMD (int /*<<< orphan*/ ,char) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SETFNB ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ db_eget (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,size_t*,int*) ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  v_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ v_isempty (int /*<<< orphan*/ *,size_t) ; 

int
v_paragraphf(SCR *sp, VICMD *vp)
{
	enum { P_INTEXT, P_INBLANK } pstate;
	size_t lastlen, len;
	recno_t cnt, lastlno, lno;
	int isempty;
	CHAR_T *p;
	char *lp;

	/*
	 * !!!
	 * If the starting cursor position is at or before any non-blank
	 * characters in the line, i.e. the movement is cutting all of the
	 * line's text, the buffer is in line mode.  It's a lot easier to
	 * check here, because we know that the end is going to be the start
	 * or end of a line.
	 *
	 * This was historical practice in vi, with a single exception.  If
	 * the paragraph movement was from the start of the last line to EOF,
	 * then all the characters were deleted from the last line, but the
	 * line itself remained.  If somebody complains, don't pause, don't
	 * hesitate, just hit them.
	 */
	if (ISMOTION(vp))
		if (vp->m_start.cno == 0)
			F_SET(vp, VM_LMODE);
		else {
			vp->m_stop = vp->m_start;
			vp->m_stop.cno = 0;
			if (nonblank(sp, vp->m_stop.lno, &vp->m_stop.cno))
				return (1);
			if (vp->m_start.cno <= vp->m_stop.cno)
				F_SET(vp, VM_LMODE);
		}

	/* Figure out what state we're currently in. */
	lno = vp->m_start.lno;
	if (db_get(sp, lno, 0, &p, &len))
		goto eof;

	/*
	 * If we start in text, we want to switch states
	 * (2 * N - 1) times, in non-text, (2 * N) times.
	 */
	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	cnt *= 2;
	if (len == 0 || v_isempty(p, len))
		pstate = P_INBLANK;
	else {
		--cnt;
		pstate = P_INTEXT;
	}

	for (;;) {
		lastlno = lno;
		lastlen = len;
		if (db_get(sp, ++lno, 0, &p, &len))
			goto eof;
		switch (pstate) {
		case P_INTEXT:
			INTEXT_CHECK;
			break;
		case P_INBLANK:
			if (len == 0 || v_isempty(p, len))
				break;
			if (--cnt) {
				pstate = P_INTEXT;
				break;
			}
			/*
			 * !!!
			 * Non-motion commands move to the end of the range,
			 * delete and yank stay at the start.  Ignore others.
			 * Adjust the end of the range for motion commands;
			 * historically, a motion component was to the end of
			 * the previous line, whereas the movement command was
			 * to the start of the new "paragraph".
			 */
found:			if (ISMOTION(vp)) {
				vp->m_stop.lno = lastlno;
				vp->m_stop.cno = lastlen ? lastlen - 1 : 0;
				vp->m_final = vp->m_start;
			} else {
				vp->m_stop.lno = lno;
				vp->m_stop.cno = 0;
				vp->m_final = vp->m_stop;
			}
			return (0);
		default:
			abort();
		}
	}

	/*
	 * !!!
	 * Adjust end of the range for motion commands; EOF is a movement
	 * sink.  The } command historically moved to the end of the last
	 * line, not the beginning, from any position before the end of the
	 * last line.  It also historically worked on empty files, so we
	 * have to make it okay.
	 */
eof:	if (vp->m_start.lno == lno || vp->m_start.lno == lno - 1) {
		if (db_eget(sp, vp->m_start.lno, &p, &len, &isempty)) {
			if (!isempty)
				return (1);
			vp->m_start.cno = 0;
			return (0);
		}
		if (vp->m_start.cno == (len ? len - 1 : 0)) {
			v_eof(sp, NULL);
			return (1);
		}
	}
	/*
	 * !!!
	 * Non-motion commands move to the end of the range, delete
	 * and yank stay at the start.  Ignore others.
	 *
	 * If deleting the line (which happens if deleting to EOF), then
	 * cursor movement is to the first nonblank.
	 */
	if (ISMOTION(vp) && ISCMD(vp->rkp, 'd')) {
		F_CLR(vp, VM_RCM_MASK);
		F_SET(vp, VM_RCM_SETFNB);
	}
	vp->m_stop.lno = lno - 1;
	vp->m_stop.cno = len ? len - 1 : 0;
	vp->m_final = ISMOTION(vp) ? vp->m_start : vp->m_stop;
	return (0);
}