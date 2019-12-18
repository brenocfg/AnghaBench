#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  coff; int /*<<< orphan*/  roff; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; void* cl_private; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  CL_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/ * CLP (TYPE_1__*) ; 
 scalar_t__ CLSP (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_LAYOUT ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delwin (scalar_t__) ; 
 int /*<<< orphan*/  stdscr ; 
 void* subwin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cl_split(SCR *origp, SCR *newp)
{
	CL_PRIVATE *clp;

	clp = CLP(origp);
	F_SET(clp, CL_LAYOUT);

	if (CLSP(origp))
		delwin(CLSP(origp));

	origp->cl_private = subwin(stdscr, origp->rows, origp->cols,
				     origp->roff, origp->coff);
	newp->cl_private = subwin(stdscr, newp->rows, newp->cols,
				     newp->roff, newp->coff);

	/* origp is the original screen, giving up space to newp. */
	return (0);
}