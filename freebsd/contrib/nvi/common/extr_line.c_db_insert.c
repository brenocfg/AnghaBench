#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  lno ;
struct TYPE_22__ {int (* put ) (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_21__ {scalar_t__* data; int size; } ;
struct TYPE_20__ {scalar_t__ c_lno; scalar_t__ c_nlines; TYPE_4__* db; } ;
struct TYPE_19__ {TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;
typedef  TYPE_3__ DBT ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOFILEYET ; 
 int /*<<< orphan*/  F_FIRSTMODIFY ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2FILE (TYPE_1__*,int /*<<< orphan*/ *,size_t,char*,size_t) ; 
 int /*<<< orphan*/  LINE_INSERT ; 
 int /*<<< orphan*/  LOG_LINE_INSERT ; 
 int /*<<< orphan*/  MIN (size_t,int) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  R_IBEFORE ; 
 int /*<<< orphan*/  TRACE (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_emsg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_g_insdel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_line (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mark_insdel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_init (TYPE_1__*) ; 
 scalar_t__ scr_update (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
db_insert(
	SCR *sp,
	recno_t lno,
	CHAR_T *p,
	size_t len)
{
	DBT data, key;
	EXF *ep;
	char *fp;
	size_t flen;
	int rval;

#if defined(DEBUG) && 0
	TRACE(sp, "insert before %lu: len %lu {%.*s}\n",
	    (u_long)lno, (u_long)len, MIN(len, 20), p);
#endif
	/* Check for no underlying file. */
	if ((ep = sp->ep) == NULL) {
		ex_emsg(sp, NULL, EXM_NOFILEYET);
		return (1);
	}
		
	INT2FILE(sp, p, len, fp, flen);
		
	/* Update file. */
	key.data = &lno;
	key.size = sizeof(lno);
	data.data = fp;
	data.size = flen;
	if (ep->db->put(ep->db, &key, &data, R_IBEFORE) == -1) {
		msgq(sp, M_SYSERR,
		    "005|unable to insert at line %lu", (u_long)lno);
		return (1);
	}

	/* Flush the cache, update line count, before screen update. */
	if (lno >= ep->c_lno)
		ep->c_lno = OOBLNO;
	if (ep->c_nlines != OOBLNO)
		++ep->c_nlines;

	/* File now dirty. */
	if (F_ISSET(ep, F_FIRSTMODIFY))
		(void)rcv_init(sp);
	F_SET(ep, F_MODIFIED);

	/* Log change. */
	log_line(sp, lno, LOG_LINE_INSERT);

	/* Update marks, @ and global commands. */
	rval = 0;
	if (mark_insdel(sp, LINE_INSERT, lno))
		rval = 1;
	if (ex_g_insdel(sp, LINE_INSERT, lno))
		rval = 1;

	/* Update screen. */
	return (scr_update(sp, lno, LINE_INSERT, 1) || rval);
}