#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_13__ {int (* put ) (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int* data; int size; } ;
struct TYPE_11__ {int* l_lp; int l_cur; int l_high; TYPE_4__* log; int /*<<< orphan*/  l_cursor; int /*<<< orphan*/  l_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  MARK ;
typedef  TYPE_2__ EXF ;
typedef  TYPE_3__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETC (TYPE_1__*,int*,int /*<<< orphan*/ ,int) ; 
 int LOG_CURSOR_INIT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRACE (TYPE_1__*,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int*,int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
log_cursor1(
	SCR *sp,
	int type)
{
	DBT data, key;
	EXF *ep;

	ep = sp->ep;

	BINC_RETC(sp, ep->l_lp, ep->l_len, sizeof(u_char) + sizeof(MARK));
	ep->l_lp[0] = type;
	memmove(ep->l_lp + sizeof(u_char), &ep->l_cursor, sizeof(MARK));

	key.data = &ep->l_cur;
	key.size = sizeof(recno_t);
	data.data = ep->l_lp;
	data.size = sizeof(u_char) + sizeof(MARK);
	if (ep->log->put(ep->log, &key, &data, 0) == -1)
		LOG_ERR;

#if defined(DEBUG) && 0
	TRACE(sp, "%lu: %s: %u/%u\n", ep->l_cur,
	    type == LOG_CURSOR_INIT ? "log_cursor_init" : "log_cursor_end",
	    sp->lno, sp->cno);
#endif
	/* Reset high water mark. */
	ep->l_high = ++ep->l_cur;

	return (0);
}