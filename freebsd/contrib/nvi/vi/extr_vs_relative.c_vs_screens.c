#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_8__ {scalar_t__ ss_lno; size_t ss_screens; } ;
struct TYPE_7__ {size_t cols; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 scalar_t__ O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 TYPE_4__* VIP (TYPE_1__*) ; 
 size_t vs_columns (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,size_t*,int /*<<< orphan*/ *) ; 

size_t
vs_screens(SCR *sp, recno_t lno, size_t *cnop)
{
	size_t cols, screens;

	/* Left-right screens are simple, it's always 1. */
	if (O_ISSET(sp, O_LEFTRIGHT))
		return (1);

	/*
	 * Check for a cached value.  We maintain a cache because, if the
	 * line is large, this routine gets called repeatedly.  One other
	 * hack, lots of time the cursor is on column one, which is an easy
	 * one.
	 */
	if (cnop == NULL) {
		if (VIP(sp)->ss_lno == lno)
			return (VIP(sp)->ss_screens);
	} else if (*cnop == 0)
		return (1);

	/* Figure out how many columns the line/column needs. */
	cols = vs_columns(sp, NULL, lno, cnop, NULL);

	screens = (cols / sp->cols + (cols % sp->cols ? 1 : 0));
	if (screens == 0)
		screens = 1;

	/* Cache the value. */
	if (cnop == NULL) {
		VIP(sp)->ss_lno = lno;
		VIP(sp)->ss_screens = screens;
	}
	return (screens);
}