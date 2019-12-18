#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lno; scalar_t__ cno; } ;
struct TYPE_6__ {int l_high; int l_cur; int /*<<< orphan*/ * log; TYPE_1__ l_cursor; scalar_t__ l_len; int /*<<< orphan*/ * l_lp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  DB_RECNO ; 
 int /*<<< orphan*/  F_NOLOG ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int O_CREAT ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/ * dbopen (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
log_init(
	SCR *sp,
	EXF *ep)
{
	/*
	 * !!!
	 * ep MAY NOT BE THE SAME AS sp->ep, DON'T USE THE LATTER.
	 *
	 * Initialize the buffer.  The logging subsystem has its own
	 * buffers because the global ones are almost by definition
	 * going to be in use when the log runs.
	 */
	ep->l_lp = NULL;
	ep->l_len = 0;
	ep->l_cursor.lno = 1;		/* XXX Any valid recno. */
	ep->l_cursor.cno = 0;
	ep->l_high = ep->l_cur = 1;

	ep->log = dbopen(NULL, O_CREAT | O_NONBLOCK | O_RDWR,
	    S_IRUSR | S_IWUSR, DB_RECNO, NULL);
	if (ep->log == NULL) {
		msgq(sp, M_SYSERR, "009|Log file");
		F_SET(ep, F_NOLOG);
		return (1);
	}

	return (0);
}