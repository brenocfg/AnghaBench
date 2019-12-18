#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_int ;
struct TYPE_23__ {int lno; size_t cno; } ;
struct TYPE_22__ {int lno; size_t cno; } ;
struct TYPE_24__ {int count; scalar_t__ key; int flags; struct TYPE_24__* kp; TYPE_2__ m_final; TYPE_1__ m_stop; TYPE_1__ m_start; struct TYPE_24__* rkp; scalar_t__ (* func ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_3__ VICMD ;
struct TYPE_25__ {int lno; size_t cno; } ;
typedef  TYPE_4__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int) ; 
 int F_ISSET (TYPE_3__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int) ; 
 scalar_t__ GC_OK ; 
 int /*<<< orphan*/  LF_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int VC_C1RESET ; 
 int VC_C1SET ; 
 int VC_ISDOT ; 
 int /*<<< orphan*/  VIM_EMPTY ; 
 int VM_COMMASK ; 
 int VM_LDOUBLE ; 
 int VM_LMODE ; 
 int /*<<< orphan*/  VM_RCM ; 
 int VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SET ; 
 int V_DOT ; 
 int /*<<< orphan*/  db_exist (TYPE_4__*,int) ; 
 scalar_t__ db_get (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__ tmotion ; 
 scalar_t__ v_cmd (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  v_emsg (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* vikeys ; 

__attribute__((used)) static int
v_motion(
	SCR *sp,
	VICMD *dm,
	VICMD *vp,
	int *mappedp)
{
	VICMD motion;
	size_t len;
	u_long cnt;
	u_int flags;
	int tilde_reset, notused;

	/*
	 * If '.' command, use the dot motion, else get the motion command.
	 * Clear any line motion flags, the subsequent motion isn't always
	 * the same, i.e. "/aaa" may or may not be a line motion.
	 */
	if (F_ISSET(vp, VC_ISDOT)) {
		motion = *dm;
		F_SET(&motion, VC_ISDOT);
		F_CLR(&motion, VM_COMMASK);
	} else {
		memset(&motion, 0, sizeof(VICMD));
		if (v_cmd(sp, NULL, &motion, vp, &notused, mappedp) != GC_OK)
			return (1);
	}

	/*
	 * A count may be provided both to the command and to the motion, in
	 * which case the count is multiplicative.  For example, "3y4y" is the
	 * same as "12yy".  This count is provided to the motion command and
	 * not to the regular function.
	 */
	cnt = motion.count = F_ISSET(&motion, VC_C1SET) ? motion.count : 1;
	if (F_ISSET(vp, VC_C1SET)) {
		motion.count *= vp->count;
		F_SET(&motion, VC_C1SET);

		/*
		 * Set flags to restore the original values of the command
		 * structure so dot commands can change the count values,
		 * e.g. "2dw" "3." deletes a total of five words.
		 */
		F_CLR(vp, VC_C1SET);
		F_SET(vp, VC_C1RESET);
	}

	/*
	 * Some commands can be repeated to indicate the current line.  In
	 * this case, or if the command is a "line command", set the flags
	 * appropriately.  If not a doubled command, run the function to get
	 * the resulting mark.
 	 */
	if (vp->key == motion.key) {
		F_SET(vp, VM_LDOUBLE | VM_LMODE);

		/* Set the origin of the command. */
		vp->m_start.lno = sp->lno;
		vp->m_start.cno = 0;

		/*
		 * Set the end of the command.
		 *
		 * If the current line is missing, i.e. the file is empty,
		 * historic vi permitted a "cc" or "!!" command to insert
		 * text.
		 */
		vp->m_stop.lno = sp->lno + motion.count - 1;
		if (db_get(sp, vp->m_stop.lno, 0, NULL, &len)) {
			if (vp->m_stop.lno != 1 ||
			   (vp->key != 'c' && vp->key != '!')) {
				v_emsg(sp, NULL, VIM_EMPTY);
				return (1);
			}
			vp->m_stop.cno = 0;
		} else
			vp->m_stop.cno = len ? len - 1 : 0;
	} else {
		/*
		 * Motion commands change the underlying movement (*snarl*).
		 * For example, "l" is illegal at the end of a line, but "dl"
		 * is not.  Set flags so the function knows the situation.
		 */
		motion.rkp = vp->kp;

		/*
		 * XXX
		 * Use yank instead of creating a new motion command, it's a
		 * lot easier for now.
		 */
		if (vp->kp == &tmotion) {
			tilde_reset = 1;
			vp->kp = &vikeys['y'];
		} else
			tilde_reset = 0;

		/*
		 * Copy the key flags into the local structure, except for the
		 * RCM flags -- the motion command will set the RCM flags in
		 * the vp structure if necessary.  This means that the motion
		 * command is expected to determine where the cursor ends up!
		 * However, we save off the current RCM mask and restore it if
		 * it no RCM flags are set by the motion command, with a small
		 * modification.
		 *
		 * We replace the VM_RCM_SET flag with the VM_RCM flag.  This
		 * is so that cursor movement doesn't set the relative position
		 * unless the motion command explicitly specified it.  This
		 * appears to match historic practice, but I've never been able
		 * to develop a hard-and-fast rule.
		 */
		flags = F_ISSET(vp, VM_RCM_MASK);
		if (LF_ISSET(VM_RCM_SET)) {
			LF_SET(VM_RCM);
			LF_CLR(VM_RCM_SET);
		}
		F_CLR(vp, VM_RCM_MASK);
		F_SET(&motion, motion.kp->flags & ~VM_RCM_MASK);

		/*
		 * Set the three cursor locations to the current cursor.  This
		 * permits commands like 'j' and 'k', that are line oriented
		 * motions and have special cursor suck semantics when they are
		 * used as standalone commands, to ignore column positioning.
		 */
		motion.m_final.lno =
		    motion.m_stop.lno = motion.m_start.lno = sp->lno;
		motion.m_final.cno =
		    motion.m_stop.cno = motion.m_start.cno = sp->cno;

		/* Run the function. */
		if ((motion.kp->func)(sp, &motion))
			return (1);

		/*
		 * If the current line is missing, i.e. the file is empty,
		 * historic vi allowed "c<motion>" or "!<motion>" to insert
		 * text.  Otherwise fail -- most motion commands will have
		 * already failed, but some, e.g. G, succeed in empty files.
		 */
		if (!db_exist(sp, vp->m_stop.lno)) {
			if (vp->m_stop.lno != 1 ||
			   (vp->key != 'c' && vp->key != '!')) {
				v_emsg(sp, NULL, VIM_EMPTY);
				return (1);
			}
			vp->m_stop.cno = 0;
		}

		/*
		 * XXX
		 * See above.
		 */
		if (tilde_reset)
			vp->kp = &tmotion;

		/*
		 * Copy cut buffer, line mode and cursor position information
		 * from the motion command structure, i.e. anything that the
		 * motion command can set for us.  The commands can flag the
		 * movement as a line motion (see v_sentence) as well as set
		 * the VM_RCM_* flags explicitly.
		 */
		F_SET(vp, F_ISSET(&motion, VM_COMMASK | VM_RCM_MASK));

		/*
		 * If the motion command set no relative motion flags, use
		 * the (slightly) modified previous values.
		 */
		if (!F_ISSET(vp, VM_RCM_MASK))
			F_SET(vp, flags);

		/*
		 * Commands can change behaviors based on the motion command
		 * used, for example, the ! command repeated the last bang
		 * command if N or n was used as the motion.
		 */
		vp->rkp = motion.kp;

		/*
		 * Motion commands can reset all of the cursor information.
		 * If the motion is in the reverse direction, switch the
		 * from and to MARK's so that it's in a forward direction.
		 * Motions are from the from MARK to the to MARK (inclusive).
		 */
		if (motion.m_start.lno > motion.m_stop.lno ||
		    (motion.m_start.lno == motion.m_stop.lno &&
		    motion.m_start.cno > motion.m_stop.cno)) {
			vp->m_start = motion.m_stop;
			vp->m_stop = motion.m_start;
		} else {
			vp->m_start = motion.m_start;
			vp->m_stop = motion.m_stop;
		}
		vp->m_final = motion.m_final;
	}

	/*
	 * If the command sets dot, save the motion structure.  The motion
	 * count was changed above and needs to be reset, that's why this
	 * is done here, and not in the calling routine.
	 */
	if (F_ISSET(vp->kp, V_DOT)) {
		*dm = motion;
		dm->count = cnt;
	}
	return (0);
}