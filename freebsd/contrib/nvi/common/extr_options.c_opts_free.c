#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * opts; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_GLOBAL ; 
 scalar_t__ OPT_STR ; 
 int /*<<< orphan*/ * O_D_STR (TYPE_1__*,int) ; 
 int O_OPTIONCOUNT ; 
 int /*<<< orphan*/ * O_STR (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_3__* optlist ; 

void
opts_free(SCR *sp)
{
	int cnt;

	for (cnt = 0; cnt < O_OPTIONCOUNT; ++cnt) {
		if (optlist[cnt].type != OPT_STR ||
		    F_ISSET(&sp->opts[cnt], OPT_GLOBAL))
			continue;
		if (O_STR(sp, cnt) != NULL)
			free(O_STR(sp, cnt));
		if (O_D_STR(sp, cnt) != NULL)
			free(O_D_STR(sp, cnt));
	}
}