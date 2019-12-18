#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int xo_indent; int xo_indent_by; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 scalar_t__ XOF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 scalar_t__ XOIF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_TOP_EMITTED ; 
 TYPE_1__* xo_default (TYPE_1__*) ; 

__attribute__((used)) static int
xo_indent (xo_handle_t *xop)
{
    int rc = 0;

    xop = xo_default(xop);

    if (XOF_ISSET(xop, XOF_PRETTY)) {
	rc = xop->xo_indent * xop->xo_indent_by;
	if (XOIF_ISSET(xop, XOIF_TOP_EMITTED))
	    rc += xop->xo_indent_by;
    }

    return (rc > 0) ? rc : 0;
}