#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
struct TYPE_17__ {size_t xo_depth; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;
typedef  int ssize_t ;
struct TYPE_16__ {int xs_flags; } ;

/* Variables and functions */
 scalar_t__ XOF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_NO_TOP ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOIF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_TOP_EMITTED ; 
 char* XO_FAILURE_NAME ; 
 int /*<<< orphan*/  XO_OP_OPEN_LEAF_LIST ; 
#define  XO_STYLE_ENCODER 129 
#define  XO_STYLE_JSON 128 
 int XSF_LIST ; 
 int XSF_NOT_FIRST ; 
 int /*<<< orphan*/  XSS_OPEN_LEAF_LIST ; 
 TYPE_2__* xo_default (TYPE_2__*) ; 
 int /*<<< orphan*/  xo_depth_change (TYPE_2__*,char const*,int,int,int /*<<< orphan*/ ,int) ; 
 int xo_encoder_handle (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_failure (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xo_indent (TYPE_2__*) ; 
 int xo_printf (TYPE_2__*,char*,char const*,char*,char const*,...) ; 
 int xo_stack_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_stack_set_flags (TYPE_2__*) ; 
 int xo_style (TYPE_2__*) ; 

__attribute__((used)) static int
xo_do_open_leaf_list (xo_handle_t *xop, xo_xof_flags_t flags, const char *name)
{
    ssize_t rc = 0;
    int indent = 0;

    xop = xo_default(xop);

    const char *ppn = XOF_ISSET(xop, XOF_PRETTY) ? "\n" : "";
    const char *pre_nl = "";

    switch (xo_style(xop)) {
    case XO_STYLE_JSON:
	indent = 1;

	if (!XOF_ISSET(xop, XOF_NO_TOP)) {
	    if (!XOIF_ISSET(xop, XOIF_TOP_EMITTED)) {
		xo_printf(xop, "%*s{%s", xo_indent(xop), "", ppn);
		XOIF_SET(xop, XOIF_TOP_EMITTED);
	    }
	}

	if (name == NULL) {
	    xo_failure(xop, "NULL passed for list name");
	    name = XO_FAILURE_NAME;
	}

	xo_stack_set_flags(xop);

	if (xop->xo_stack[xop->xo_depth].xs_flags & XSF_NOT_FIRST)
	    pre_nl = XOF_ISSET(xop, XOF_PRETTY) ? ",\n" : ", ";
	xop->xo_stack[xop->xo_depth].xs_flags |= XSF_NOT_FIRST;

	rc = xo_printf(xop, "%s%*s\"%s\": [%s",
		       pre_nl, xo_indent(xop), "", name, ppn);
	break;

    case XO_STYLE_ENCODER:
	rc = xo_encoder_handle(xop, XO_OP_OPEN_LEAF_LIST, name, NULL, flags);
	break;
    }

    xo_depth_change(xop, name, 1, indent, XSS_OPEN_LEAF_LIST,
		    XSF_LIST | xo_stack_flags(flags));

    return rc;
}