#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lno; size_t cno; } ;
struct TYPE_10__ {TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_11__ {int lno; size_t cno; } ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SET ; 
 scalar_t__ db_eget (TYPE_3__*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
v_ex_done(SCR *sp, VICMD *vp)
{
	size_t len;

	/*
	 * The only cursor modifications are real, however, the underlying
	 * line may have changed; don't trust anything.  This code has been
	 * a remarkably fertile place for bugs.  Do a reality check on a
	 * cursor value, and make sure it's okay.  If necessary, change it.
	 * Ex keeps track of the line number, but it cares less about the
	 * column and it may have disappeared.
	 *
	 * Don't trust ANYTHING.
	 *
	 * XXX
	 * Ex will soon have to start handling the column correctly; see
	 * the POSIX 1003.2 standard.
	 */
	if (db_eget(sp, sp->lno, NULL, &len, NULL)) {
		sp->lno = 1;
		sp->cno = 0;
	} else if (sp->cno >= len)
		sp->cno = len ? len - 1 : 0;

	vp->m_final.lno = sp->lno;
	vp->m_final.cno = sp->cno;

	/*
	 * Don't re-adjust the cursor after executing an ex command,
	 * and ex movements are permanent.
	 */
	F_CLR(vp, VM_RCM_MASK);
	F_SET(vp, VM_RCM_SET);

	return (0);
}