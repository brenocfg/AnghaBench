#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int xs_flags; scalar_t__ xs_name; int /*<<< orphan*/  xs_state; } ;
typedef  TYPE_1__ xo_stack_t ;
struct TYPE_7__ {int xo_depth; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* xo_default (TYPE_2__*) ; 
 char* xo_state_name (int /*<<< orphan*/ ) ; 

void
xo_dump_stack (xo_handle_t *xop)
{
    int i;
    xo_stack_t *xsp;

    xop = xo_default(xop);

    fprintf(stderr, "Stack dump:\n");

    xsp = xop->xo_stack;
    for (i = 1, xsp++; i <= xop->xo_depth; i++, xsp++) {
	fprintf(stderr, "   [%d] %s '%s' [%x]\n",
		i, xo_state_name(xsp->xs_state),
		xsp->xs_name ?: "--", xsp->xs_flags);
    }
}