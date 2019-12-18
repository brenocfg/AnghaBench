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
typedef  int recno_t ;
struct TYPE_7__ {scalar_t__ cno; int lno; } ;
struct TYPE_8__ {int count; TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FATAL ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  O_SECTIONS ; 
 char* O_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  v_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_sectionf(SCR *sp, VICMD *vp)
{
	recno_t cnt, lno;
	size_t len;
	CHAR_T *p;
	char *list, *lp;

	/* Get the macro list. */
	if ((list = O_STR(sp, O_SECTIONS)) == NULL)
		return (1);

	/*
	 * !!!
	 * If the starting cursor position is at or before any non-blank
	 * characters in the line, i.e. the movement is cutting all of the
	 * line's text, the buffer is in line mode.  It's a lot easier to
	 * check here, because we know that the end is going to be the start
	 * or end of a line.
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

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	for (lno = vp->m_start.lno; !db_get(sp, ++lno, 0, &p, &len);) {
		if (len == 0)
			continue;
		if (p[0] == '{' || (ISMOTION(vp) && p[0] == '}')) {
			if (!--cnt) {
				if (p[0] == '{')
					goto adjust1;
				goto adjust2;
			}
			continue;
		}
		/*
		 * !!!
		 * Historic documentation (USD:15-11, 4.2) said that formfeed
		 * characters (^L) in the first column delimited sections.
		 * The historic code mentions formfeed characters, but never
		 * implements them.  Seems reasonable, do it.
		 */
		if (p[0] == '\014') {
			if (!--cnt)
				goto adjust1;
			continue;
		}
		if (p[0] != '.' || len < 2)
			continue;
		for (lp = list; *lp != '\0'; lp += 2 * sizeof(*lp))
			if (lp[0] == p[1] &&
			    ((lp[1] == ' ' && len == 2) || lp[1] == p[2]) &&
			    !--cnt) {
				/*
				 * !!!
				 * If not cutting this line, adjust to the end
				 * of the previous one.  Otherwise, position to
				 * column 0.
				 */
adjust1:			if (ISMOTION(vp))
					goto ret1;

adjust2:			vp->m_stop.lno = lno;
				vp->m_stop.cno = 0;
				goto ret2;
			}
	}

	/* If moving forward, reached EOF, check to see if we started there. */
	if (vp->m_start.lno == lno - 1) {
		v_eof(sp, NULL);
		return (1);
	}

ret1:	if (db_get(sp, --lno, DBG_FATAL, NULL, &len))
		return (1);
	vp->m_stop.lno = lno;
	vp->m_stop.cno = len ? len - 1 : 0;

	/*
	 * Non-motion commands go to the end of the range.  Delete and
	 * yank stay at the start of the range.  Ignore others.
	 */
ret2:	if (ISMOTION(vp)) {
		vp->m_final = vp->m_start;
		if (F_ISSET(vp, VM_LMODE))
			vp->m_final.cno = 0;
	} else
		vp->m_final = vp->m_stop;
	return (0);
}