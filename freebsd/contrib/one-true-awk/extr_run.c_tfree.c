#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* cnext; int /*<<< orphan*/  sval; int /*<<< orphan*/  tval; int /*<<< orphan*/  nval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  NN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ freeable (TYPE_1__*) ; 
 TYPE_1__* tmps ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void tfree(Cell *a)	/* free a tempcell */
{
	if (freeable(a)) {
		   dprintf( ("freeing %s %s %o\n", NN(a->nval), NN(a->sval), a->tval) );
		xfree(a->sval);
	}
	if (a == tmps)
		FATAL("tempcell list is curdled");
	a->cnext = tmps;
	tmps = a;
}