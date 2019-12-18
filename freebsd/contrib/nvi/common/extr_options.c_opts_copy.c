#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_9__ {int /*<<< orphan*/ * opts; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  OPT_GLOBAL ; 
 scalar_t__ OPT_STR ; 
 int OS_DEF ; 
 int OS_NOFREE ; 
 int OS_STR ; 
 int OS_STRDUP ; 
 int /*<<< orphan*/ * O_D_STR (TYPE_1__*,int) ; 
 int O_OPTIONCOUNT ; 
 int /*<<< orphan*/ * O_STR (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ o_set (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* optlist ; 

int
opts_copy(
	SCR *orig,
	SCR *sp)
{
	int cnt, rval;

	/* Copy most everything without change. */
	memcpy(sp->opts, orig->opts, sizeof(orig->opts));

	/* Copy the string edit options. */
	for (cnt = rval = 0; cnt < O_OPTIONCOUNT; ++cnt) {
		if (optlist[cnt].type != OPT_STR ||
		    F_ISSET(&sp->opts[cnt], OPT_GLOBAL))
			continue;
		/*
		 * If never set, or already failed, NULL out the entries --
		 * have to continue after failure, otherwise would have two
		 * screens referencing the same memory.
		 */
		if (rval || O_STR(sp, cnt) == NULL) {
			o_set(sp, cnt, OS_NOFREE | OS_STR, NULL, 0);
			o_set(sp, cnt, OS_DEF | OS_NOFREE | OS_STR, NULL, 0);
			continue;
		}

		/* Copy the current string. */
		if (o_set(sp, cnt, OS_NOFREE | OS_STRDUP, O_STR(sp, cnt), 0)) {
			o_set(sp, cnt, OS_DEF | OS_NOFREE | OS_STR, NULL, 0);
			goto nomem;
		}

		/* Copy the default string. */
		if (O_D_STR(sp, cnt) != NULL && o_set(sp, cnt,
		    OS_DEF | OS_NOFREE | OS_STRDUP, O_D_STR(sp, cnt), 0)) {
nomem:			msgq(orig, M_SYSERR, NULL);
			rval = 1;
		}
	}
	return (rval);
}