#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum which { ____Placeholder_which } which ;
typedef  int /*<<< orphan*/  dir_t ;
struct TYPE_8__ {scalar_t__ lno; size_t cno; } ;
struct TYPE_7__ {TYPE_2__ m_stop; TYPE_2__ m_start; TYPE_2__ m_final; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ MARK ;

/* Variables and functions */
 int /*<<< orphan*/  BACKWARD ; 
#define  BQMARK 129 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  FORWARD ; 
#define  FQMARK 128 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_1__*) ; 
 int /*<<< orphan*/  M_BERR ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ mark_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  v_nomove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mark(SCR *sp, VICMD *vp, int getmark, enum which cmd)
{
	dir_t dir;
	MARK m;
	size_t len;

	if (getmark && mark_get(sp, vp->character, &vp->m_stop, M_BERR))
		return (1);

	/*
	 * !!!
	 * Historically, BQMARKS for character positions that no longer
	 * existed acted as FQMARKS.
	 *
	 * FQMARKS move to the first non-blank.
	 */
	switch (cmd) {
	case BQMARK:
		if (db_get(sp, vp->m_stop.lno, DBG_FATAL, NULL, &len))
			return (1);
		if (vp->m_stop.cno < len ||
		    (vp->m_stop.cno == len && len == 0))
			break;

		if (ISMOTION(vp))
			F_SET(vp, VM_LMODE);
		cmd = FQMARK;
		/* FALLTHROUGH */
	case FQMARK:
		vp->m_stop.cno = 0;
		if (nonblank(sp, vp->m_stop.lno, &vp->m_stop.cno))
			return (1);
		break;
	default:
		abort();
	}

	/* Non-motion commands move to the end of the range. */
	if (!ISMOTION(vp)) {
		vp->m_final = vp->m_stop;
		return (0);
	}

	/*
	 * !!!
	 * If a motion component to a BQMARK, the cursor has to move.
	 */
	if (cmd == BQMARK &&
	    vp->m_stop.lno == vp->m_start.lno &&
	    vp->m_stop.cno == vp->m_start.cno) {
		v_nomove(sp);
		return (1);
	}

	/*
	 * If the motion is in the reverse direction, switch the start and
	 * stop MARK's so that it's in a forward direction.  (There's no
	 * reason for this other than to make the tests below easier.  The
	 * code in vi.c:vi() would have done the switch.)  Both forward
	 * and backward motions can happen for any kind of search command.
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
	 * Yank cursor motion, when associated with marks as motion commands,
	 * historically behaved as follows:
	 *
	 * ` motion			' motion
	 *		Line change?		Line change?
	 *		Y	N		Y	N
	 *	      --------------	      ---------------
	 * FORWARD:  |	NM	NM	      | NM	NM
	 *	     |			      |
	 * BACKWARD: |	M	M	      | M	NM(1)
	 *
	 * where NM means the cursor didn't move, and M means the cursor
	 * moved to the mark.
	 *
	 * As the cursor was usually moved for yank commands associated
	 * with backward motions, this implementation regularizes it by
	 * changing the NM at position (1) to be an M.  This makes mark
	 * motions match search motions, which is probably A Good Thing.
	 *
	 * Delete cursor motion was always to the start of the text region,
	 * regardless.  Ignore other motion commands.
	 */
	vp->m_final = vp->m_start;

	/*
	 * Forward marks are always line oriented, and it's set in the
	 * vcmd.c table.
	 */
	if (cmd == FQMARK)
		return (0);

	/*
	 * BQMARK'S moving backward and starting at column 0, and ones moving
	 * forward and ending at column 0 are corrected to the last column of
	 * the previous line.  Otherwise, adjust the starting/ending point to
	 * the character before the current one (this is safe because we know
	 * the search had to move to succeed).
	 *
	 * Mark motions become line mode opertions if they start at the first
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