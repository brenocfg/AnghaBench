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
struct TYPE_9__ {int lno; scalar_t__ cno; } ;
struct TYPE_8__ {int lno; scalar_t__ cno; } ;
struct TYPE_10__ {int count; TYPE_2__ m_stop; TYPE_2__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_3__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_SECTIONS ; 
 char* O_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SETFNB ; 
 int /*<<< orphan*/  db_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/  v_sof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_sectionb(SCR *sp, VICMD *vp)
{
	size_t len;
	recno_t cnt, lno;
	CHAR_T *p;
	char *list, *lp;

	/* An empty file or starting from line 1 is always illegal. */
	if (vp->m_start.lno <= 1) {
		v_sof(sp, NULL);
		return (1);
	}

	/* Get the macro list. */
	if ((list = O_STR(sp, O_SECTIONS)) == NULL)
		return (1);

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	for (lno = vp->m_start.lno; !db_get(sp, --lno, 0, &p, &len);) {
		if (len == 0)
			continue;
		if (p[0] == '{') {
			if (!--cnt)
				goto adjust1;
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
adjust1:			vp->m_stop.lno = lno;
				vp->m_stop.cno = 0;
				goto ret1;
			}
	}

	/*
	 * If moving backward, reached SOF, which is a movement sink.
	 * We already checked for starting there.
	 */
	vp->m_stop.lno = 1;
	vp->m_stop.cno = 0;

	/*
	 * All commands move to the end of the range.
	 *
	 * !!!
	 * Historic practice is the section cut was in line mode if it started
	 * from column 0 and was in the backward direction.  Otherwise, left
	 * motion commands adjust the starting point to the character before
	 * the current one.  What makes this worse is that if it cut to line
	 * mode it also went to the first non-<blank>.
	 */
ret1:	if (vp->m_start.cno == 0) {
		F_CLR(vp, VM_RCM_MASK);
		F_SET(vp, VM_RCM_SETFNB);

		--vp->m_start.lno;
		F_SET(vp, VM_LMODE);
	} else
		--vp->m_start.cno;

	vp->m_final = vp->m_stop;
	return (0);
}