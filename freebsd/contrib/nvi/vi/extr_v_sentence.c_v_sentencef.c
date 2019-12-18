#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_11__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_12__ {int count; TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_13__ {scalar_t__ cs_lno; scalar_t__ cs_cno; scalar_t__ cs_flags; int cs_ch; } ;
typedef  TYPE_3__ VCS ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ CS_EMP ; 
 scalar_t__ CS_EOF ; 
 scalar_t__ CS_EOL ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 scalar_t__ cs_fblank (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ cs_init (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ cs_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ isblank (int) ; 
 int /*<<< orphan*/  v_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_sentencef(SCR *sp, VICMD *vp)
{
	enum { BLANK, NONE, PERIOD } state;
	VCS cs;
	size_t len;
	u_long cnt;

	cs.cs_lno = vp->m_start.lno;
	cs.cs_cno = vp->m_start.cno;
	if (cs_init(sp, &cs))
		return (1);

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;

	/*
	 * !!!
	 * If in white-space, the next start of sentence counts as one.
	 * This may not handle "  .  " correctly, but it's real unclear
	 * what correctly means in that case.
	 */
	if (cs.cs_flags == CS_EMP || (cs.cs_flags == 0 && isblank(cs.cs_ch))) {
		if (cs_fblank(sp, &cs))
			return (1);
		if (--cnt == 0) {
			if (vp->m_start.lno != cs.cs_lno ||
			    vp->m_start.cno != cs.cs_cno)
				goto okret;
			return (1);
		}
	}

	for (state = NONE;;) {
		if (cs_next(sp, &cs))
			return (1);
		if (cs.cs_flags == CS_EOF)
			break;
		if (cs.cs_flags == CS_EOL) {
			if ((state == PERIOD || state == BLANK) && --cnt == 0) {
				if (cs_next(sp, &cs))
					return (1);
				if (cs.cs_flags == 0 &&
				    isblank(cs.cs_ch) && cs_fblank(sp, &cs))
					return (1);
				goto okret;
			}
			state = NONE;
			continue;
		}
		if (cs.cs_flags == CS_EMP) {	/* An EMP is two sentences. */
			if (--cnt == 0)
				goto okret;
			if (cs_fblank(sp, &cs))
				return (1);
			if (--cnt == 0)
				goto okret;
			state = NONE;
			continue;
		}
		switch (cs.cs_ch) {
		case '.':
		case '?':
		case '!':
			state = PERIOD;
			break;
		case ')':
		case ']':
		case '"':
		case '\'':
			if (state != PERIOD)
				state = NONE;
			break;
		case '\t':
			if (state == PERIOD)
				state = BLANK;
			/* FALLTHROUGH */
		case ' ':
			if (state == PERIOD) {
				state = BLANK;
				break;
			}
			if (state == BLANK && --cnt == 0) {
				if (cs_fblank(sp, &cs))
					return (1);
				goto okret;
			}
			/* FALLTHROUGH */
		default:
			state = NONE;
			break;
		}
	}

	/* EOF is a movement sink, but it's an error not to have moved. */
	if (vp->m_start.lno == cs.cs_lno && vp->m_start.cno == cs.cs_cno) {
		v_eof(sp, NULL);
		return (1);
	}

okret:	vp->m_stop.lno = cs.cs_lno;
	vp->m_stop.cno = cs.cs_cno;

	/*
	 * !!!
	 * Historic, uh, features, yeah, that's right, call 'em features.
	 * If the starting and ending cursor positions are at the first
	 * column in their lines, i.e. the movement is cutting entire lines,
	 * the buffer is in line mode, and the ending position is the last
	 * character of the previous line.  Note check to make sure that
	 * it's not within a single line.
	 *
	 * Non-motion commands move to the end of the range.  Delete and
	 * yank stay at the start.  Ignore others.  Adjust the end of the
	 * range for motion commands.
	 */
	if (ISMOTION(vp)) {
		if (vp->m_start.cno == 0 &&
		    (cs.cs_flags != 0 || vp->m_stop.cno == 0)) {
			if (vp->m_start.lno < vp->m_stop.lno) {
				if (db_get(sp,
				    --vp->m_stop.lno, DBG_FATAL, NULL, &len))
					return (1);
				vp->m_stop.cno = len ? len - 1 : 0;
			}
			F_SET(vp, VM_LMODE);
		} else
			--vp->m_stop.cno;
		vp->m_final = vp->m_start;
	} else
		vp->m_final = vp->m_stop;
	return (0);
}