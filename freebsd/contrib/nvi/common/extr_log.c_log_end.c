#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int lno; scalar_t__ cno; } ;
struct TYPE_6__ {int l_high; int l_cur; TYPE_1__ l_cursor; scalar_t__ l_len; int /*<<< orphan*/ * l_lp; TYPE_3__* log; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

int
log_end(
	SCR *sp,
	EXF *ep)
{
	/*
	 * !!!
	 * ep MAY NOT BE THE SAME AS sp->ep, DON'T USE THE LATTER.
	 */
	if (ep->log != NULL) {
		(void)(ep->log->close)(ep->log);
		ep->log = NULL;
	}
	if (ep->l_lp != NULL) {
		free(ep->l_lp);
		ep->l_lp = NULL;
	}
	ep->l_len = 0;
	ep->l_cursor.lno = 1;		/* XXX Any valid recno. */
	ep->l_cursor.cno = 0;
	ep->l_high = ep->l_cur = 1;
	return (0);
}