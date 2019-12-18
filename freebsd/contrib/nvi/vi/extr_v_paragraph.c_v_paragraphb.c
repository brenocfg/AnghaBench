#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_8__ {int lno; scalar_t__ cno; } ;
struct TYPE_10__ {int lno; scalar_t__ cno; } ;
struct TYPE_9__ {int count; TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_3__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEXT_CHECK ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ v_isempty (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  v_sof (int /*<<< orphan*/ *,TYPE_3__*) ; 

int
v_paragraphb(SCR *sp, VICMD *vp)
{
	enum { P_INTEXT, P_INBLANK } pstate;
	size_t len;
	recno_t cnt, lno;
	CHAR_T *p;
	char *lp;

	/*
	 * !!!
	 * Check for SOF.  The historic vi didn't complain if users hit SOF
	 * repeatedly, unless it was part of a motion command.  There is no
	 * question but that Emerson's editor of choice was vi.
	 *
	 * The { command historically moved to the beginning of the first
	 * line if invoked on the first line.
	 *
	 * !!!
	 * If the starting cursor position is in the first column (backward
	 * paragraph movements did NOT historically pay attention to non-blank
	 * characters) i.e. the movement is cutting the entire line, the buffer
	 * is in line mode.  Cuts from the beginning of the line also did not
	 * cut the current line, but started at the previous EOL.
	 *
	 * Correct for a left motion component while we're thinking about it.
	 */
	lno = vp->m_start.lno;

	if (ISMOTION(vp))
		if (vp->m_start.cno == 0) {
			if (vp->m_start.lno == 1) {
				v_sof(sp, &vp->m_start);
				return (1);
			} else
				--vp->m_start.lno;
			F_SET(vp, VM_LMODE);
		} else
			--vp->m_start.cno;

	if (vp->m_start.lno <= 1)
		goto sof;

	/* Figure out what state we're currently in. */
	if (db_get(sp, lno, 0, &p, &len))
		goto sof;

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

		/*
		 * !!!
		 * If the starting cursor is past the first column,
		 * the current line is checked for a paragraph.
		 */
		if (vp->m_start.cno > 0)
			++lno;
	}

	for (;;) {
		if (db_get(sp, --lno, 0, &p, &len))
			goto sof;
		switch (pstate) {
		case P_INTEXT:
			INTEXT_CHECK;
			break;
		case P_INBLANK:
			if (len != 0 && !v_isempty(p, len)) {
				if (!--cnt)
					goto found;
				pstate = P_INTEXT;
			}
			break;
		default:
			abort();
		}
	}

	/* SOF is a movement sink. */
sof:	lno = 1;

found:	vp->m_stop.lno = lno;
	vp->m_stop.cno = 0;

	/*
	 * All commands move to the end of the range.  (We already
	 * adjusted the start of the range for motion commands).
	 */
	vp->m_final = vp->m_stop;
	return (0);
}