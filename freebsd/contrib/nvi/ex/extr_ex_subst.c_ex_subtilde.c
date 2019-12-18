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
struct TYPE_12__ {int /*<<< orphan*/  re_c; int /*<<< orphan*/  re_len; int /*<<< orphan*/ * re; } ;
struct TYPE_11__ {int /*<<< orphan*/ * bp; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOPREVRE ; 
 int /*<<< orphan*/  F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RE_C_SEARCH ; 
 int /*<<< orphan*/  SC_RE_SEARCH ; 
 int /*<<< orphan*/  ex_emsg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ re_compile (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int s (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ex_subtilde(SCR *sp, EXCMD *cmdp)
{
	if (sp->re == NULL) {
		ex_emsg(sp, NULL, EXM_NOPREVRE);
		return (1);
	}
	if (!F_ISSET(sp, SC_RE_SEARCH) && re_compile(sp, sp->re,
	    sp->re_len, NULL, NULL, &sp->re_c, RE_C_SEARCH))
		return (1);
	return (s(sp,
	    cmdp, cmdp->argc ? cmdp->argv[0]->bp : NULL, &sp->re_c, 0));
}