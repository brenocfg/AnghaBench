#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  lno ;
struct TYPE_20__ {int (* del ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {scalar_t__* data; int size; } ;
struct TYPE_18__ {scalar_t__ c_lno; scalar_t__ c_nlines; TYPE_4__* db; } ;
struct TYPE_17__ {TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;
typedef  TYPE_3__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOFILEYET ; 
 int /*<<< orphan*/  F_FIRSTMODIFY ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINE_DELETE ; 
 int /*<<< orphan*/  LOG_LINE_DELETE ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  TRACE (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_emsg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_g_insdel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_line (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mark_insdel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_init (TYPE_1__*) ; 
 int scr_update (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
db_delete(
	SCR *sp,
	recno_t lno)
{
	DBT key;
	EXF *ep;

#if defined(DEBUG) && 0
	TRACE(sp, "delete line %lu\n", (u_long)lno);
#endif
	/* Check for no underlying file. */
	if ((ep = sp->ep) == NULL) {
		ex_emsg(sp, NULL, EXM_NOFILEYET);
		return (1);
	}
		
	/* Update marks, @ and global commands. */
	if (mark_insdel(sp, LINE_DELETE, lno))
		return (1);
	if (ex_g_insdel(sp, LINE_DELETE, lno))
		return (1);

	/* Log change. */
	log_line(sp, lno, LOG_LINE_DELETE);

	/* Update file. */
	key.data = &lno;
	key.size = sizeof(lno);
	if (ep->db->del(ep->db, &key, 0) == 1) {
		msgq(sp, M_SYSERR,
		    "003|unable to delete line %lu", (u_long)lno);
		return (1);
	}

	/* Flush the cache, update line count, before screen update. */
	if (lno <= ep->c_lno)
		ep->c_lno = OOBLNO;
	if (ep->c_nlines != OOBLNO)
		--ep->c_nlines;

	/* File now modified. */
	if (F_ISSET(ep, F_FIRSTMODIFY))
		(void)rcv_init(sp);
	F_SET(ep, F_MODIFIED);

	/* Update screen. */
	return (scr_update(sp, lno, LINE_DELETE, 1));
}