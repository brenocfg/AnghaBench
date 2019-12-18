#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int recno_t ;
struct TYPE_20__ {int (* put ) (TYPE_5__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {int* data; int size; } ;
struct TYPE_16__ {scalar_t__ lno; } ;
struct TYPE_18__ {int* l_lp; int l_cur; int l_high; TYPE_5__* log; int /*<<< orphan*/  l_len; TYPE_1__ l_cursor; } ;
struct TYPE_17__ {TYPE_3__* ep; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;
typedef  TYPE_4__ DBT ;
typedef  int CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETC (TYPE_2__*,int*,int /*<<< orphan*/ ,int) ; 
 int CHAR_T_OFFSET ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  DBG_NOCACHE ; 
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_NOLOG ; 
 int /*<<< orphan*/  F_UNDO ; 
 int* L (char*) ; 
 int /*<<< orphan*/  LOG_CURSOR_INIT ; 
 int /*<<< orphan*/  LOG_ERR ; 
#define  LOG_LINE_APPEND 132 
#define  LOG_LINE_DELETE 131 
#define  LOG_LINE_INSERT 130 
#define  LOG_LINE_RESET_B 129 
#define  LOG_LINE_RESET_F 128 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  TRACE (TYPE_2__*,char*,int,int,size_t) ; 
 int /*<<< orphan*/  db_err (TYPE_2__*,int) ; 
 scalar_t__ db_get (TYPE_2__*,int,int /*<<< orphan*/ ,int**,size_t*) ; 
 scalar_t__ log_cursor1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 
 int stub1 (TYPE_5__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

int
log_line(
	SCR *sp,
	recno_t lno,
	u_int action)
{
	DBT data, key;
	EXF *ep;
	size_t len;
	CHAR_T *lp;
	recno_t lcur;

	ep = sp->ep;
	if (F_ISSET(ep, F_NOLOG))
		return (0);

	/*
	 * XXX
	 *
	 * Kluge for vi.  Clear the EXF undo flag so that the
	 * next 'u' command does a roll-back, regardless.
	 */
	F_CLR(ep, F_UNDO);

	/* Put out one initial cursor record per set of changes. */
	if (ep->l_cursor.lno != OOBLNO) {
		if (log_cursor1(sp, LOG_CURSOR_INIT))
			return (1);
		ep->l_cursor.lno = OOBLNO;
	}

	/*
	 * Put out the changes.  If it's a LOG_LINE_RESET_B call, it's a
	 * special case, avoid the caches.  Also, if it fails and it's
	 * line 1, it just means that the user started with an empty file,
	 * so fake an empty length line.
	 */
	if (action == LOG_LINE_RESET_B) {
		if (db_get(sp, lno, DBG_NOCACHE, &lp, &len)) {
			if (lno != 1) {
				db_err(sp, lno);
				return (1);
			}
			len = 0;
			lp = L("");
		}
	} else
		if (db_get(sp, lno, DBG_FATAL, &lp, &len))
			return (1);
	BINC_RETC(sp,
	    ep->l_lp, ep->l_len,
	    len * sizeof(CHAR_T) + CHAR_T_OFFSET);
	ep->l_lp[0] = action;
	memmove(ep->l_lp + sizeof(u_char), &lno, sizeof(recno_t));
	memmove(ep->l_lp + CHAR_T_OFFSET, lp, len * sizeof(CHAR_T));

	lcur = ep->l_cur;
	key.data = &lcur;
	key.size = sizeof(recno_t);
	data.data = ep->l_lp;
	data.size = len * sizeof(CHAR_T) + CHAR_T_OFFSET;
	if (ep->log->put(ep->log, &key, &data, 0) == -1)
		LOG_ERR;

#if defined(DEBUG) && 0
	switch (action) {
	case LOG_LINE_APPEND:
		TRACE(sp, "%lu: log_line: append: %lu {%u}\n",
		    ep->l_cur, lno, len);
		break;
	case LOG_LINE_DELETE:
		TRACE(sp, "%lu: log_line: delete: %lu {%u}\n",
		    ep->l_cur, lno, len);
		break;
	case LOG_LINE_INSERT:
		TRACE(sp, "%lu: log_line: insert: %lu {%u}\n",
		    ep->l_cur, lno, len);
		break;
	case LOG_LINE_RESET_F:
		TRACE(sp, "%lu: log_line: reset_f: %lu {%u}\n",
		    ep->l_cur, lno, len);
		break;
	case LOG_LINE_RESET_B:
		TRACE(sp, "%lu: log_line: reset_b: %lu {%u}\n",
		    ep->l_cur, lno, len);
		break;
	}
#endif
	/* Reset high water mark. */
	ep->l_high = ++ep->l_cur;

	return (0);
}