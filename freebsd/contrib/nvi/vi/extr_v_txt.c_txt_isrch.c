#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int ;
typedef  scalar_t__ recno_t ;
struct TYPE_33__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_30__ {TYPE_5__ m_final; TYPE_5__ m_start; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_34__ {scalar_t__ lno; } ;
struct TYPE_32__ {TYPE_1__* gp; int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_31__ {int cno; char* lb; scalar_t__ lno; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* scr_refresh ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ TEXT ;
typedef  TYPE_4__ SCR ;
typedef  TYPE_5__ MARK ;

/* Variables and functions */
 int /*<<< orphan*/  FL_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CLR (TYPE_4__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_4__*,int) ; 
 scalar_t__ IS_ONELINE (TYPE_4__*) ; 
 int /*<<< orphan*/  IS_RESTART ; 
 int /*<<< orphan*/  IS_RUNNING ; 
 scalar_t__ IS_SHELLMETA (TYPE_4__*,char) ; 
 int /*<<< orphan*/  KEYS_WAITING (TYPE_4__*) ; 
 int SC_TINPUT ; 
 int SC_TINPUT_INFO ; 
 int SEARCH_INCR ; 
 int SEARCH_SET ; 
 TYPE_8__* TMAP ; 
 TYPE_4__* VIP (TYPE_4__*) ; 
 int VIP_S_MODELINE ; 
 int /*<<< orphan*/  b_search (TYPE_4__*,TYPE_5__*,TYPE_5__*,char*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  f_search (TYPE_4__*,TYPE_5__*,TYPE_5__*,char*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ txt_map_end (TYPE_4__*) ; 
 scalar_t__ txt_map_init (TYPE_4__*) ; 
 scalar_t__ vs_line (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vs_refresh (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_isrch(SCR *sp, VICMD *vp, TEXT *tp, u_int8_t *is_flagsp)
{
	MARK start;
	recno_t lno;
	u_int sf;

	/* If it's a one-line screen, we don't do incrementals. */
	if (IS_ONELINE(sp)) {
		FL_CLR(*is_flagsp, IS_RUNNING);
		return (0);
	}

	/*
	 * If the user erases back to the beginning of the buffer, there's
	 * nothing to search for.  Reset the cursor to the starting point.
	 */
	if (tp->cno <= 1) {
		vp->m_final = vp->m_start;
		return (0);
	}

	/*
	 * If it's an RE quote character, and not quoted, ignore it until
	 * we get another character.
	 */
	if (tp->lb[tp->cno - 1] == '\\' &&
	    (tp->cno == 2 || tp->lb[tp->cno - 2] != '\\'))
		return (0);

	/*
	 * If it's a magic shell character, and not quoted, reset the cursor
	 * to the starting point.
	 */
	if (IS_SHELLMETA(sp, tp->lb[tp->cno - 1]) &&
	    (tp->cno == 2 || tp->lb[tp->cno - 2] != '\\'))
		vp->m_final = vp->m_start;

	/*
	 * If we see the search pattern termination character, then quit doing
	 * an incremental search.  There may be more, e.g., ":/foo/;/bar/",
	 * and we can't handle that incrementally.  Also, reset the cursor to
	 * the original location, the ex search routines don't know anything
	 * about incremental searches.
	 */
	if (tp->lb[0] == tp->lb[tp->cno - 1] &&
	    (tp->cno == 2 || tp->lb[tp->cno - 2] != '\\')) {
		vp->m_final = vp->m_start;
		FL_CLR(*is_flagsp, IS_RUNNING);
		return (0);
	}
		
	/*
	 * Remember the input line and discard the special input map,
	 * but don't overwrite the input line on the screen.
	 */
	lno = tp->lno;
	F_SET(VIP(sp), VIP_S_MODELINE);
	F_CLR(sp, SC_TINPUT | SC_TINPUT_INFO);
	if (txt_map_end(sp))
		return (1);

	/*
	 * Specify a starting point and search.  If we find a match, move to
	 * it and refresh the screen.  If we didn't find the match, then we
	 * beep the screen.  When searching from the original cursor position, 
	 * we have to move the cursor, otherwise, we don't want to move the
	 * cursor in case the text at the current position continues to match.
	 */
	if (FL_ISSET(*is_flagsp, IS_RESTART)) {
		start = vp->m_start;
		sf = SEARCH_SET;
	} else {
		start = vp->m_final;
		sf = SEARCH_INCR | SEARCH_SET;
	}

	if (tp->lb[0] == '/' ?
	    !f_search(sp,
	    &start, &vp->m_final, tp->lb + 1, tp->cno - 1, NULL, sf) :
	    !b_search(sp,
	    &start, &vp->m_final, tp->lb + 1, tp->cno - 1, NULL, sf)) {
		sp->lno = vp->m_final.lno;
		sp->cno = vp->m_final.cno;
		FL_CLR(*is_flagsp, IS_RESTART);

		if (!KEYS_WAITING(sp) && vs_refresh(sp, 0))
			return (1);
	} else
		FL_SET(*is_flagsp, IS_RESTART);

	/* Reinstantiate the special input map. */
	if (txt_map_init(sp))
		return (1);
	F_CLR(VIP(sp), VIP_S_MODELINE);
	F_SET(sp, SC_TINPUT | SC_TINPUT_INFO);

	/* Reset the line number of the input line. */
	tp->lno = TMAP[0].lno; 

	/*
	 * If the colon command-line moved, i.e. the screen scrolled,
	 * refresh the input line.
	 *
	 * XXX
	 * We shouldn't be calling vs_line, here -- we need dirty bits
	 * on entries in the SMAP array.
	 */
	if (lno != TMAP[0].lno) {
		if (vs_line(sp, &TMAP[0], NULL, NULL))
			return (1);
		(void)sp->gp->scr_refresh(sp, 0);
	}
	return (0);
}