#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* xs_name; int xs_flags; } ;
typedef  TYPE_1__ xo_stack_t ;
struct TYPE_16__ {size_t xo_depth; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ XOF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 char* XO_FAILURE_NAME ; 
 int /*<<< orphan*/  XO_OP_CLOSE_CONTAINER ; 
#define  XO_STYLE_ENCODER 133 
#define  XO_STYLE_HTML 132 
#define  XO_STYLE_JSON 131 
#define  XO_STYLE_SDPARAMS 130 
#define  XO_STYLE_TEXT 129 
#define  XO_STYLE_XML 128 
 int XSF_DTRT ; 
 int XSF_NOT_FIRST ; 
 int /*<<< orphan*/  XSS_CLOSE_CONTAINER ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 TYPE_2__* xo_default (TYPE_2__*) ; 
 int /*<<< orphan*/  xo_depth_change (TYPE_2__*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xo_encoder_handle (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_failure (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xo_indent (TYPE_2__*) ; 
 int xo_printf (TYPE_2__*,char*,char const*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  xo_stack_set_flags (TYPE_2__*) ; 
 int xo_style (TYPE_2__*) ; 
 char* xo_xml_leader (TYPE_2__*,char const*) ; 

__attribute__((used)) static int
xo_do_close_container (xo_handle_t *xop, const char *name)
{
    xop = xo_default(xop);

    ssize_t rc = 0;
    const char *ppn = XOF_ISSET(xop, XOF_PRETTY) ? "\n" : "";
    const char *pre_nl = "";

    if (name == NULL) {
	xo_stack_t *xsp = &xop->xo_stack[xop->xo_depth];

	name = xsp->xs_name;
	if (name) {
	    ssize_t len = strlen(name) + 1;
	    /* We need to make a local copy; xo_depth_change will free it */
	    char *cp = alloca(len);
	    memcpy(cp, name, len);
	    name = cp;
	} else if (!(xsp->xs_flags & XSF_DTRT)) {
	    xo_failure(xop, "missing name without 'dtrt' mode");
	    name = XO_FAILURE_NAME;
	}
    }

    const char *leader = xo_xml_leader(xop, name);

    switch (xo_style(xop)) {
    case XO_STYLE_XML:
	xo_depth_change(xop, name, -1, -1, XSS_CLOSE_CONTAINER, 0);
	rc = xo_printf(xop, "%*s</%s%s>%s", xo_indent(xop), "", leader, name, ppn);
	break;

    case XO_STYLE_JSON:
	xo_stack_set_flags(xop);

	pre_nl = XOF_ISSET(xop, XOF_PRETTY) ? "\n" : "";
	ppn = "";

	xo_depth_change(xop, name, -1, -1, XSS_CLOSE_CONTAINER, 0);
	rc = xo_printf(xop, "%s%*s}%s", pre_nl, xo_indent(xop), "", ppn);
	xop->xo_stack[xop->xo_depth].xs_flags |= XSF_NOT_FIRST;
	break;

    case XO_STYLE_HTML:
    case XO_STYLE_TEXT:
	xo_depth_change(xop, name, -1, 0, XSS_CLOSE_CONTAINER, 0);
	break;

    case XO_STYLE_SDPARAMS:
	break;

    case XO_STYLE_ENCODER:
	xo_depth_change(xop, name, -1, 0, XSS_CLOSE_CONTAINER, 0);
	rc = xo_encoder_handle(xop, XO_OP_CLOSE_CONTAINER, name, NULL, 0);
	break;
    }

    return rc;
}