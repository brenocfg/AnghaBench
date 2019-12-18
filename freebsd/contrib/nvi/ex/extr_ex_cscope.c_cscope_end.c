#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cscq; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;

/* Variables and functions */
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ ) ; 
 scalar_t__ terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
cscope_end(SCR *sp)
{
	EX_PRIVATE *exp;

	for (exp = EXP(sp); !SLIST_EMPTY(exp->cscq);)
		if (terminate(sp, NULL, 1))
			return (1);
	return (0);
}