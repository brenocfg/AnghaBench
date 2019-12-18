#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;

/* Type definitions */
typedef  int recno_t ;
typedef  int lnop_t ;
struct TYPE_21__ {int totalcount; } ;
typedef  TYPE_2__ VI_PRIVATE ;
struct TYPE_23__ {size_t t_rows; int lno; TYPE_1__* gp; } ;
struct TYPE_22__ {int lno; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* scr_move ) (TYPE_4__*,size_t,size_t) ;int /*<<< orphan*/  (* scr_cursor ) (TYPE_4__*,size_t*,size_t*) ;} ;
struct TYPE_19__ {int lno; } ;
typedef  TYPE_3__ SMAP ;
typedef  TYPE_4__ SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* HMAP ; 
#define  LINE_APPEND 131 
#define  LINE_DELETE 130 
#define  LINE_INSERT 129 
#define  LINE_RESET 128 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  SC_TINPUT_INFO ; 
 TYPE_15__* TMAP ; 
 TYPE_2__* VIP (TYPE_4__*) ; 
 int /*<<< orphan*/  VIP_CUR_INVALID ; 
 int /*<<< orphan*/  VIP_N_EX_REDRAW ; 
 int /*<<< orphan*/  VIP_N_REFRESH ; 
 int /*<<< orphan*/  VIP_N_RENUMBER ; 
 int /*<<< orphan*/  VI_SCR_CFLUSH (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  db_exist (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,size_t*,size_t*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,size_t,size_t) ; 
 int /*<<< orphan*/  vs_sm_delete (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vs_sm_insert (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vs_sm_reset (TYPE_4__*,int) ; 

int
vs_change(SCR *sp, recno_t lno, lnop_t op)
{
	VI_PRIVATE *vip;
	SMAP *p;
	size_t cnt, oldy, oldx;

	vip = VIP(sp);

	/*
	 * XXX
	 * Very nasty special case.  The historic vi code displays a single
	 * space (or a '$' if the list option is set) for the first line in
	 * an "empty" file.  If we "insert" a line, that line gets scrolled
	 * down, not repainted, so it's incorrect when we refresh the screen.
	 * The vi text input functions detect it explicitly and don't insert
	 * a new line.
	 *
	 * Check for line #2 before going to the end of the file.
	 */
	if (((op == LINE_APPEND && lno == 0) || 
	    (op == LINE_INSERT && lno == 1)) &&
	    !db_exist(sp, 2)) {
		lno = 1;
		op = LINE_RESET;
	}

	/* Appending is the same as inserting, if the line is incremented. */
	if (op == LINE_APPEND) {
		++lno;
		op = LINE_INSERT;
	}

	/* Ignore the change if the line is after the map. */
	if (lno > TMAP->lno)
		return (0);

	/*
	 * If the line is before the map, and it's a decrement, decrement
	 * the map.  If it's an increment, increment the map.  Otherwise,
	 * ignore it.
	 */
	if (lno < HMAP->lno) {
		switch (op) {
		case LINE_APPEND:
			abort();
			/* NOTREACHED */
		case LINE_DELETE:
			for (p = HMAP, cnt = sp->t_rows; cnt--; ++p)
				--p->lno;
			if (sp->lno >= lno)
				--sp->lno;
			F_SET(vip, VIP_N_RENUMBER);
			break;
		case LINE_INSERT:
			for (p = HMAP, cnt = sp->t_rows; cnt--; ++p)
				++p->lno;
			if (sp->lno >= lno)
				++sp->lno;
			F_SET(vip, VIP_N_RENUMBER);
			break;
		case LINE_RESET:
			break;
		}
		return (0);
	}

	F_SET(vip, VIP_N_REFRESH);

	/*
	 * Invalidate the line size cache, and invalidate the cursor if it's
	 * on this line,
	 */
	VI_SCR_CFLUSH(vip);
	if (sp->lno == lno)
		F_SET(vip, VIP_CUR_INVALID);

	/*
	 * If ex modifies the screen after ex output is already on the screen
	 * or if we've switched into ex canonical mode, don't touch it -- we'll
	 * get scrolling wrong, at best.
	 */
	if (!F_ISSET(sp, SC_TINPUT_INFO) &&
	    (F_ISSET(sp, SC_SCR_EXWROTE) || VIP(sp)->totalcount > 1)) {
		F_SET(vip, VIP_N_EX_REDRAW);
		return (0);
	}

	/* Save and restore the cursor for these routines. */
	(void)sp->gp->scr_cursor(sp, &oldy, &oldx);

	switch (op) {
	case LINE_DELETE:
		if (vs_sm_delete(sp, lno))
			return (1);
		if (sp->lno > lno)
			--sp->lno;
		F_SET(vip, VIP_N_RENUMBER);
		break;
	case LINE_INSERT:
		if (vs_sm_insert(sp, lno))
			return (1);
		if (sp->lno > lno)
			++sp->lno;
		F_SET(vip, VIP_N_RENUMBER);
		break;
	case LINE_RESET:
		if (vs_sm_reset(sp, lno))
			return (1);
		break;
	default:
		abort();
	}

	(void)sp->gp->scr_move(sp, oldy, oldx);
	return (0);
}