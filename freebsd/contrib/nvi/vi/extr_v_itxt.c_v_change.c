#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_28__ {scalar_t__ lno; size_t cno; } ;
struct TYPE_31__ {scalar_t__ lno; } ;
struct TYPE_29__ {int count; TYPE_14__ m_start; TYPE_5__ m_stop; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_30__ {scalar_t__ lno; size_t cno; int /*<<< orphan*/  showmode; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int CUT_LINEMODE ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  FREE_SPACEW (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SPACE_RETW (TYPE_2__*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  LF_SET (int) ; 
 int /*<<< orphan*/  LOG_CORRECT ; 
 int /*<<< orphan*/  MEMMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  O_AUTOINDENT ; 
 scalar_t__ O_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CHANGE ; 
 int TXT_AICHARS ; 
 int TXT_APPENDEOL ; 
 int TXT_EMARK ; 
 int TXT_OVERWRITE ; 
 int /*<<< orphan*/  VC_BUFFER ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SET ; 
 scalar_t__ cut (TYPE_2__*,int /*<<< orphan*/ *,TYPE_14__*,TYPE_5__*,int) ; 
 scalar_t__ db_eget (TYPE_2__*,scalar_t__,int /*<<< orphan*/ **,size_t*,int*) ; 
 scalar_t__ db_get (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ db_insert (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ del (TYPE_2__*,TYPE_14__*,TYPE_5__*,int) ; 
 scalar_t__ nonblank (TYPE_2__*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  set_txt_std (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int v_ia (TYPE_2__*,TYPE_1__*) ; 
 int v_txt (TYPE_2__*,TYPE_1__*,TYPE_5__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
v_change(SCR *sp, VICMD *vp)
{
	size_t blen, len;
	u_int32_t flags;
	int isempty, lmode, rval;
	CHAR_T *bp;
	CHAR_T *p;

	/*
	 * 'c' can be combined with motion commands that set the resulting
	 * cursor position, i.e. "cG".  Clear the VM_RCM flags and make the
	 * resulting cursor position stick, inserting text has its own rules
	 * for cursor positioning.
	 */
	F_CLR(vp, VM_RCM_MASK);
	F_SET(vp, VM_RCM_SET);

	/*
	 * Find out if the file is empty, it's easier to handle it as a
	 * special case.
	 */
	if (vp->m_start.lno == vp->m_stop.lno &&
	    db_eget(sp, vp->m_start.lno, &p, &len, &isempty)) {
		if (!isempty)
			return (1);
		return (v_ia(sp, vp));
	}

	flags = set_txt_std(sp, vp, 0);
	sp->showmode = SM_CHANGE;

	/*
	 * Move the cursor to the start of the change.  Note, if autoindent
	 * is turned on, the cc command in line mode changes from the first
	 * *non-blank* character of the line, not the first character.  And,
	 * to make it just a bit more exciting, the initial space is handled
	 * as auto-indent characters.
	 */
	lmode = F_ISSET(vp, VM_LMODE) ? CUT_LINEMODE : 0;
	if (lmode) {
		vp->m_start.cno = 0;
		if (O_ISSET(sp, O_AUTOINDENT)) {
			if (nonblank(sp, vp->m_start.lno, &vp->m_start.cno))
				return (1);
			LF_SET(TXT_AICHARS);
		}
	}
	sp->lno = vp->m_start.lno;
	sp->cno = vp->m_start.cno;

	LOG_CORRECT;

	/*
	 * If not in line mode and changing within a single line, copy the
	 * text and overwrite it.
	 */
	if (!lmode && vp->m_start.lno == vp->m_stop.lno) {
		/*
		 * !!!
		 * Historic practice, c did not cut into the numeric buffers,
		 * only the unnamed one.
		 */
		if (cut(sp,
		    F_ISSET(vp, VC_BUFFER) ? &vp->buffer : NULL,
		    &vp->m_start, &vp->m_stop, lmode))
			return (1);
		if (len == 0)
			LF_SET(TXT_APPENDEOL);
		LF_SET(TXT_EMARK | TXT_OVERWRITE);
		return (v_txt(sp, vp, &vp->m_stop, p, len,
		    0, OOBLNO, F_ISSET(vp, VC_C1SET) ? vp->count : 1, flags));
	}

	/*
	 * It's trickier if in line mode or changing over multiple lines.  If
	 * we're in line mode delete all of the lines and insert a replacement
	 * line which the user edits.  If there was leading whitespace in the
	 * first line being changed, we copy it and use it as the replacement.
	 * If we're not in line mode, we delete the text and start inserting.
	 *
	 * !!!
	 * Copy the text.  Historic practice, c did not cut into the numeric
	 * buffers, only the unnamed one.
	 */
	if (cut(sp,
	    F_ISSET(vp, VC_BUFFER) ? &vp->buffer : NULL,
	    &vp->m_start, &vp->m_stop, lmode))
		return (1);

	/* If replacing entire lines and there's leading text. */
	if (lmode && vp->m_start.cno) {
		/*
		 * Get a copy of the first line changed, and copy out the
		 * leading text.
		 */
		if (db_get(sp, vp->m_start.lno, DBG_FATAL, &p, &len))
			return (1);
		GET_SPACE_RETW(sp, bp, blen, vp->m_start.cno);
		MEMMOVE(bp, p, vp->m_start.cno);
	} else
		bp = NULL;

	/* Delete the text. */
	if (del(sp, &vp->m_start, &vp->m_stop, lmode))
		return (1);

	/* If replacing entire lines, insert a replacement line. */
	if (lmode) {
		if (db_insert(sp, vp->m_start.lno, bp, vp->m_start.cno))
			return (1);
		sp->lno = vp->m_start.lno;
		len = sp->cno = vp->m_start.cno;
	}

	/* Get the line we're editing. */
	if (db_eget(sp, vp->m_start.lno, &p, &len, &isempty)) {
		if (!isempty)
			return (1);
		len = 0;
	}

	/* Check to see if we're appending to the line. */
	if (vp->m_start.cno >= len)
		LF_SET(TXT_APPENDEOL);

	rval = v_txt(sp, vp, NULL, p, len,
	    0, OOBLNO, F_ISSET(vp, VC_C1SET) ? vp->count : 1, flags);

	if (bp != NULL)
		FREE_SPACEW(sp, bp, blen);
	return (rval);
}