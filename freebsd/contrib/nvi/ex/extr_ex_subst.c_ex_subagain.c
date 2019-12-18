#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__** argv; scalar_t__ argc; } ;
struct TYPE_12__ {int /*<<< orphan*/  subre_c; int /*<<< orphan*/  subre_len; int /*<<< orphan*/ * subre; } ;
struct TYPE_11__ {int /*<<< orphan*/ * bp; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOPREVRE ; 
 int /*<<< orphan*/  F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RE_C_SUBST ; 
 int /*<<< orphan*/  SC_RE_SUBST ; 
 int /*<<< orphan*/  ex_emsg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ re_compile (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int s (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ex_subagain(SCR *sp, EXCMD *cmdp)
{
	if (sp->subre == NULL) {
		ex_emsg(sp, NULL, EXM_NOPREVRE);
		return (1);
	}
	if (!F_ISSET(sp, SC_RE_SUBST) &&
	    re_compile(sp, sp->subre, sp->subre_len,
	    NULL, NULL, &sp->subre_c, RE_C_SUBST))
		return (1);
	return (s(sp,
	    cmdp, cmdp->argc ? cmdp->argv[0]->bp : NULL, &sp->subre_c, 0));
}