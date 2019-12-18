#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  addr1; int /*<<< orphan*/  buffer; int /*<<< orphan*/  iflags; } ;
struct TYPE_11__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_10__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ MARK ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_BUFFER ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ put (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 

int
ex_put(SCR *sp, EXCMD *cmdp)
{
	MARK m;

	NEEDFILE(sp, cmdp);

	m.lno = sp->lno;
	m.cno = sp->cno;
	if (put(sp, NULL,
	    FL_ISSET(cmdp->iflags, E_C_BUFFER) ? &cmdp->buffer : NULL,
	    &cmdp->addr1, &m, 1))
		return (1);
	sp->lno = m.lno;
	sp->cno = m.cno;
	return (0);
}