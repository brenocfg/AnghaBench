#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lno; int /*<<< orphan*/  cno; } ;
struct TYPE_9__ {TYPE_1__ l_cursor; } ;
struct TYPE_8__ {scalar_t__ lno; int /*<<< orphan*/  cno; TYPE_3__* ep; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_NOLOG ; 
 int /*<<< orphan*/  LOG_CURSOR_END ; 
 scalar_t__ OOBLNO ; 
 int log_cursor1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
log_cursor(SCR *sp)
{
	EXF *ep;

	ep = sp->ep;
	if (F_ISSET(ep, F_NOLOG))
		return (0);

	/*
	 * If any changes were made since the last cursor init,
	 * put out the ending cursor record.
	 */
	if (ep->l_cursor.lno == OOBLNO) {
		ep->l_cursor.lno = sp->lno;
		ep->l_cursor.cno = sp->cno;
		return (log_cursor1(sp, LOG_CURSOR_END));
	}
	ep->l_cursor.lno = sp->lno;
	ep->l_cursor.cno = sp->cno;
	return (0);
}