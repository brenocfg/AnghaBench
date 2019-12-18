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
struct TYPE_4__ {scalar_t__ ccnt; scalar_t__ q_ccnt; char** cargv; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

int
ex_ncheck(SCR *sp, int force)
{
	char **ap;

	/*
	 * !!!
	 * Historic practice: quit! or two quit's done in succession
	 * (where ZZ counts as a quit) didn't check for other files.
	 */
	if (!force && sp->ccnt != sp->q_ccnt + 1 &&
	    sp->cargv != NULL && sp->cargv[1] != NULL) {
		sp->q_ccnt = sp->ccnt;

		for (ap = sp->cargv + 1; *ap != NULL; ++ap);
		msgq(sp, M_ERR,
		    "167|%d more files to edit", (int)(ap - sp->cargv) - 1);

		return (1);
	}
	return (0);
}