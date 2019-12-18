#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_21__ {int (* put ) (TYPE_6__*,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int size; scalar_t__* data; } ;
struct TYPE_16__ {scalar_t__ lno; } ;
struct TYPE_19__ {scalar_t__ l_cur; scalar_t__ l_high; TYPE_6__* log; scalar_t__* l_lp; int /*<<< orphan*/  l_len; TYPE_1__ l_cursor; } ;
struct TYPE_18__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; int /*<<< orphan*/  name; } ;
struct TYPE_17__ {TYPE_4__* ep; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ LMARK ;
typedef  TYPE_4__ EXF ;
typedef  TYPE_5__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETC (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ F_ISSET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_NOLOG ; 
 int /*<<< orphan*/  LOG_CURSOR_INIT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ LOG_MARK ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  TRACE (TYPE_2__*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ log_cursor1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,TYPE_3__*,int) ; 
 int stub1 (TYPE_6__*,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

int
log_mark(
	SCR *sp,
	LMARK *lmp)
{
	DBT data, key;
	EXF *ep;

	ep = sp->ep;
	if (F_ISSET(ep, F_NOLOG))
		return (0);

	/* Put out one initial cursor record per set of changes. */
	if (ep->l_cursor.lno != OOBLNO) {
		if (log_cursor1(sp, LOG_CURSOR_INIT))
			return (1);
		ep->l_cursor.lno = OOBLNO;
	}

	BINC_RETC(sp, ep->l_lp,
	    ep->l_len, sizeof(u_char) + sizeof(LMARK));
	ep->l_lp[0] = LOG_MARK;
	memmove(ep->l_lp + sizeof(u_char), lmp, sizeof(LMARK));

	key.data = &ep->l_cur;
	key.size = sizeof(recno_t);
	data.data = ep->l_lp;
	data.size = sizeof(u_char) + sizeof(LMARK);
	if (ep->log->put(ep->log, &key, &data, 0) == -1)
		LOG_ERR;

#if defined(DEBUG) && 0
	TRACE(sp, "%lu: mark %c: %lu/%u\n",
	    ep->l_cur, lmp->name, lmp->lno, lmp->cno);
#endif
	/* Reset high water mark. */
	ep->l_high = ++ep->l_cur;
	return (0);
}