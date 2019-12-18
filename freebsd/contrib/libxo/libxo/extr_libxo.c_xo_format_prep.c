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
typedef  int xo_xff_flags_t ;
struct TYPE_7__ {size_t xo_depth; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;
struct TYPE_6__ {int xs_flags; } ;

/* Variables and functions */
 int XFF_LEAF_LIST ; 
 scalar_t__ XOF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int XSF_NOT_FIRST ; 
 int /*<<< orphan*/  xo_data_append (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void
xo_format_prep (xo_handle_t *xop, xo_xff_flags_t flags)
{
    if (xop->xo_stack[xop->xo_depth].xs_flags & XSF_NOT_FIRST) {
	xo_data_append(xop, ",", 1);
	if (!(flags & XFF_LEAF_LIST) && XOF_ISSET(xop, XOF_PRETTY))
	    xo_data_append(xop, "\n", 1);
    } else
	xop->xo_stack[xop->xo_depth].xs_flags |= XSF_NOT_FIRST;
}