#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_3__ {scalar_t__ lno; scalar_t__ soff; } ;
typedef  TYPE_1__ SMAP ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 int vs_screens (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

recno_t
vs_sm_nlines(SCR *sp, SMAP *from_sp, recno_t to_lno, size_t max)
{
	recno_t lno, lcnt;

	if (O_ISSET(sp, O_LEFTRIGHT))
		return (from_sp->lno > to_lno ?
		    from_sp->lno - to_lno : to_lno - from_sp->lno);

	if (from_sp->lno == to_lno)
		return (from_sp->soff - 1);

	if (from_sp->lno > to_lno) {
		lcnt = from_sp->soff - 1;	/* Correct for off-by-one. */
		for (lno = from_sp->lno; --lno >= to_lno && lcnt <= max;)
			lcnt += vs_screens(sp, lno, NULL);
	} else {
		lno = from_sp->lno;
		lcnt = (vs_screens(sp, lno, NULL) - from_sp->soff) + 1;
		for (; ++lno < to_lno && lcnt <= max;)
			lcnt += vs_screens(sp, lno, NULL);
	}
	return (lcnt);
}