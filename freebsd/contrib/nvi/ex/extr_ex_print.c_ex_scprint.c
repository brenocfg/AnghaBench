#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cno; int /*<<< orphan*/  lno; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ MARK ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FATAL ; 
 scalar_t__ INTERRUPTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * L (char*) ; 
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_NUMBER ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  ex_fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ ex_prchars (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ ,char) ; 

int
ex_scprint(SCR *sp, MARK *fp, MARK *tp)
{
	CHAR_T *p;
	size_t col, len;

	col = 0;
	if (O_ISSET(sp, O_NUMBER)) {
		p = L("        ");
		if (ex_prchars(sp, p, &col, 8, 0, 0))
			return (1);
	}

	if (db_get(sp, fp->lno, DBG_FATAL, &p, &len))
		return (1);

	if (ex_prchars(sp, p, &col, fp->cno, 0, ' '))
		return (1);
	p += fp->cno;
	if (ex_prchars(sp,
	    p, &col, tp->cno == fp->cno ? 1 : tp->cno - fp->cno, 0, '^'))
		return (1);
	if (INTERRUPTED(sp))
		return (1);
	p = L("[ynq]");		/* XXX: should be msg_cat. */
	if (ex_prchars(sp, p, &col, 5, 0, 0))
		return (1);
	(void)ex_fflush(sp);
	return (0);
}