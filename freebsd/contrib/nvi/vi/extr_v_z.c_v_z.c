#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
typedef  int /*<<< orphan*/  e_key_t ;
struct TYPE_23__ {int /*<<< orphan*/  lno; int /*<<< orphan*/  cno; } ;
struct TYPE_19__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_21__ {scalar_t__ count2; int character; TYPE_2__* kp; TYPE_6__ m_final; TYPE_1__ m_start; int /*<<< orphan*/  count; } ;
typedef  TYPE_3__ VICMD ;
struct TYPE_22__ {int /*<<< orphan*/  t_rows; } ;
struct TYPE_20__ {int /*<<< orphan*/  usage; } ;
typedef  TYPE_4__ SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_VAL (TYPE_4__*,int) ; 
 int /*<<< orphan*/  K_CR ; 
 int /*<<< orphan*/  K_NL ; 
 scalar_t__ O_VAL (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_WINDOW ; 
 int /*<<< orphan*/  P_BOTTOM ; 
 int /*<<< orphan*/  P_MIDDLE ; 
 int /*<<< orphan*/  P_TOP ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VC_C2SET ; 
 int /*<<< orphan*/  VIM_USAGE ; 
 int /*<<< orphan*/  Z_CARAT ; 
 int /*<<< orphan*/  Z_PLUS ; 
 int /*<<< orphan*/  db_exist (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ db_last (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_emsg (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vs_crel (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  vs_sm_fill (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_sm_position (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_sm_scroll (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
v_z(SCR *sp, VICMD *vp)
{
	recno_t lno;
	e_key_t value;

	/*
	 * The first count is the line to use.  If the value doesn't
	 * exist, use the last line.
	 */
	if (F_ISSET(vp, VC_C1SET)) {
		lno = vp->count;
		if (!db_exist(sp, lno) && db_last(sp, &lno))
			return (1);
	} else
		lno = vp->m_start.lno;

	/* Set default return cursor line. */
	vp->m_final.lno = lno;
	vp->m_final.cno = vp->m_start.cno;

	/*
	 * The second count is the displayed window size, i.e. the 'z' command
	 * is another way to get artificially small windows.  Note, you can't
	 * grow beyond the size of the window.
	 *
	 * !!!
	 * A window size of 0 was historically allowed, and simply ignored.
	 * This could be much more simply done by modifying the value of the
	 * O_WINDOW option, but that's not how it worked historically.
	 */
	if (F_ISSET(vp, VC_C2SET) && vp->count2 != 0) {
		if (vp->count2 > O_VAL(sp, O_WINDOW))
			vp->count2 = O_VAL(sp, O_WINDOW);
		if (vs_crel(sp, vp->count2))
			return (1);
	}

	switch (vp->character) {
	case '-':		/* Put the line at the bottom. */
		if (vs_sm_fill(sp, lno, P_BOTTOM))
			return (1);
		break;
	case '.':		/* Put the line in the middle. */
		if (vs_sm_fill(sp, lno, P_MIDDLE))
			return (1);
		break;
	case '+':
		/*
		 * If the user specified a line number, put that line at the
		 * top and move the cursor to it.  Otherwise, scroll forward
		 * a screen from the current screen.
		 */
		if (F_ISSET(vp, VC_C1SET)) {
			if (vs_sm_fill(sp, lno, P_TOP))
				return (1);
			if (vs_sm_position(sp, &vp->m_final, 0, P_TOP))
				return (1);
		} else
			if (vs_sm_scroll(sp, &vp->m_final, sp->t_rows, Z_PLUS))
				return (1);
		break;
	case '^':
		/*
		 * If the user specified a line number, put that line at the
		 * bottom, move the cursor to it, and then display the screen
		 * before that one.  Otherwise, scroll backward a screen from
		 * the current screen.
		 *
		 * !!!
		 * Note, we match the off-by-one characteristics of historic
		 * vi, here.
		 */
		if (F_ISSET(vp, VC_C1SET)) {
			if (vs_sm_fill(sp, lno, P_BOTTOM))
				return (1);
			if (vs_sm_position(sp, &vp->m_final, 0, P_TOP))
				return (1);
			if (vs_sm_fill(sp, vp->m_final.lno, P_BOTTOM))
				return (1);
		} else
			if (vs_sm_scroll(sp, &vp->m_final, sp->t_rows, Z_CARAT))
				return (1);
		break;
	default:		/* Put the line at the top for <cr>. */
		value = KEY_VAL(sp, vp->character);
		if (value != K_CR && value != K_NL) {
			v_emsg(sp, vp->kp->usage, VIM_USAGE);
			return (1);
		}
		if (vs_sm_fill(sp, lno, P_TOP))
			return (1);
		break;
	}
	return (0);
}