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
struct TYPE_6__ {int /*<<< orphan*/  xs_flags; } ;
typedef  TYPE_1__ xo_stack_t ;
struct TYPE_7__ {size_t xo_depth; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_CLEAR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XOF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_NOT_FIRST ; 
 int /*<<< orphan*/  XSF_NOT_FIRST ; 

__attribute__((used)) static void
xo_stack_set_flags (xo_handle_t *xop)
{
    if (XOF_ISSET(xop, XOF_NOT_FIRST)) {
	xo_stack_t *xsp = &xop->xo_stack[xop->xo_depth];

	xsp->xs_flags |= XSF_NOT_FIRST;
	XOF_CLEAR(xop, XOF_NOT_FIRST);
    }
}