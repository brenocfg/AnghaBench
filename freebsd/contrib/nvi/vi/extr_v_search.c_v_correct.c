#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dir_t ;
struct TYPE_6__ {scalar_t__ lno; size_t cno; } ;
struct TYPE_5__ {TYPE_2__ m_stop; TYPE_2__ m_start; TYPE_2__ m_final; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ MARK ;

/* Variables and functions */
 int /*<<< orphan*/  BACKWARD ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  FORWARD ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BERR ; 
 int /*<<< orphan*/  VM_LMODE ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,scalar_t__,size_t*) ; 

int
v_correct(SCR *sp, VICMD *vp, int isdelta)
{
	dir_t dir;
	MARK m;
	size_t len;

	/*
	 * !!!
	 * We may have wrapped if wrapscan was set, and we may have returned
	 * to the position where the cursor started.  Historic vi didn't cope
	 * with this well.  Yank wouldn't beep, but the first put after the
	 * yank would move the cursor right one column (without adding any
	 * text) and the second would put a copy of the current line.  The
	 * change and delete commands would beep, but would leave the cursor
	 * on the colon command line.  I believe that there are macros that
	 * depend on delete, at least, failing.  For now, commands that use
	 * search as a motion component fail when the search returns to the
	 * original cursor position.
	 */
	if (vp->m_start.lno == vp->m_stop.lno &&
	    vp->m_start.cno == vp->m_stop.cno) {
		msgq(sp, M_BERR, "190|Search wrapped to original position");
		return (1);
	}

	/*
	 * !!!
	 * Searches become line mode operations if there was a delta specified
	 * to the search pattern.
	 */
	if (isdelta)
		F_SET(vp, VM_LMODE);

	/*
	 * If the motion is in the reverse direction, switch the start and
	 * stop MARK's so that it's in a forward direction.  (There's no
	 * reason for this other than to make the tests below easier.  The
	 * code in vi.c:vi() would have done the switch.)  Both forward
	 * and backward motions can happen for any kind of search command
	 * because of the wrapscan option.
	 */
	if (vp->m_start.lno > vp->m_stop.lno ||
	    (vp->m_start.lno == vp->m_stop.lno &&
	    vp->m_start.cno > vp->m_stop.cno)) {
		m = vp->m_start;
		vp->m_start = vp->m_stop;
		vp->m_stop = m;
		dir = BACKWARD;
	} else
		dir = FORWARD;

	/*
	 * BACKWARD:
	 *	Delete and yank commands move to the end of the range.
	 *	Ignore others.
	 *
	 * FORWARD:
	 *	Delete and yank commands don't move.  Ignore others.
	 */
	vp->m_final = vp->m_start;

	/*
	 * !!!
	 * Delta'd searches don't correct based on column positions.
	 */
	if (isdelta)
		return (0);

	/*
	 * !!!
	 * Backward searches starting at column 0, and forward searches ending
	 * at column 0 are corrected to the last column of the previous line.
	 * Otherwise, adjust the starting/ending point to the character before
	 * the current one (this is safe because we know the search had to move
	 * to succeed).
	 *
	 * Searches become line mode operations if they start at the first
	 * nonblank and end at column 0 of another line.
	 */
	if (vp->m_start.lno < vp->m_stop.lno && vp->m_stop.cno == 0) {
		if (db_get(sp, --vp->m_stop.lno, DBG_FATAL, NULL, &len))
			return (1);
		vp->m_stop.cno = len ? len - 1 : 0;
		len = 0;
		if (nonblank(sp, vp->m_start.lno, &len))
			return (1);
		if (vp->m_start.cno <= len)
			F_SET(vp, VM_LMODE);
	} else
		--vp->m_stop.cno;

	return (0);
}