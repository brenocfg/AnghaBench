#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
struct TYPE_17__ {int xb_curp; int xb_bufp; } ;
struct TYPE_19__ {size_t xo_depth; TYPE_2__* xo_stack; TYPE_1__ xo_attrs; int /*<<< orphan*/  xo_flags; } ;
typedef  TYPE_3__ xo_handle_t ;
typedef  int ssize_t ;
struct TYPE_18__ {int xs_flags; } ;

/* Variables and functions */
 scalar_t__ XOF_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 char* XO_FAILURE_NAME ; 
 int /*<<< orphan*/  XO_OP_OPEN_INSTANCE ; 
#define  XO_STYLE_ENCODER 131 
#define  XO_STYLE_JSON 130 
#define  XO_STYLE_SDPARAMS 129 
#define  XO_STYLE_XML 128 
 int XSF_NOT_FIRST ; 
 int /*<<< orphan*/  XSS_OPEN_INSTANCE ; 
 int /*<<< orphan*/  xo_data_append (TYPE_3__*,int,int) ; 
 TYPE_3__* xo_default (TYPE_3__*) ; 
 int /*<<< orphan*/  xo_depth_change (TYPE_3__*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xo_encoder_handle (TYPE_3__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_failure (TYPE_3__*,char*) ; 
 char* xo_indent (TYPE_3__*) ; 
 int xo_printf (TYPE_3__*,char*,char const*,...) ; 
 int /*<<< orphan*/  xo_stack_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_stack_set_flags (TYPE_3__*) ; 
 int xo_style (TYPE_3__*) ; 
 char* xo_xml_leader (TYPE_3__*,char const*) ; 

__attribute__((used)) static int
xo_do_open_instance (xo_handle_t *xop, xo_xof_flags_t flags, const char *name)
{
    xop = xo_default(xop);

    ssize_t rc = 0;
    const char *ppn = XOF_ISSET(xop, XOF_PRETTY) ? "\n" : "";
    const char *pre_nl = "";

    if (name == NULL) {
	xo_failure(xop, "NULL passed for instance name");
	name = XO_FAILURE_NAME;
    }

    const char *leader = xo_xml_leader(xop, name);
    flags |= xop->xo_flags;

    switch (xo_style(xop)) {
    case XO_STYLE_XML:
	rc = xo_printf(xop, "%*s<%s%s", xo_indent(xop), "", leader, name);

	if (xop->xo_attrs.xb_curp != xop->xo_attrs.xb_bufp) {
	    rc += xop->xo_attrs.xb_curp - xop->xo_attrs.xb_bufp;
	    xo_data_append(xop, xop->xo_attrs.xb_bufp,
			   xop->xo_attrs.xb_curp - xop->xo_attrs.xb_bufp);
	    xop->xo_attrs.xb_curp = xop->xo_attrs.xb_bufp;
	}

	rc += xo_printf(xop, ">%s", ppn);
	break;

    case XO_STYLE_JSON:
	xo_stack_set_flags(xop);

	if (xop->xo_stack[xop->xo_depth].xs_flags & XSF_NOT_FIRST)
	    pre_nl = XOF_ISSET(xop, XOF_PRETTY) ? ",\n" : ", ";
	xop->xo_stack[xop->xo_depth].xs_flags |= XSF_NOT_FIRST;

	rc = xo_printf(xop, "%s%*s{%s",
		       pre_nl, xo_indent(xop), "", ppn);
	break;

    case XO_STYLE_SDPARAMS:
	break;

    case XO_STYLE_ENCODER:
	rc = xo_encoder_handle(xop, XO_OP_OPEN_INSTANCE, name, NULL, flags);
	break;
    }

    xo_depth_change(xop, name, 1, 1, XSS_OPEN_INSTANCE, xo_stack_flags(flags));

    return rc;
}