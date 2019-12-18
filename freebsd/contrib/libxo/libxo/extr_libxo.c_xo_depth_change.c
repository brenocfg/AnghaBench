#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int xo_xsf_flags_t ;
typedef  int /*<<< orphan*/  xo_state_t ;
struct TYPE_9__ {int xs_flags; char* xs_name; char* xs_keys; int /*<<< orphan*/  xs_state; } ;
typedef  TYPE_1__ xo_stack_t ;
struct TYPE_10__ {int xo_depth; int xo_indent; TYPE_1__* xo_stack; } ;
typedef  TYPE_2__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_DTRT ; 
 int /*<<< orphan*/  XOF_IGNORE_CLOSE ; 
 scalar_t__ XOF_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_WARN ; 
 char* XO_FAILURE_NAME ; 
 scalar_t__ XO_STYLE_HTML ; 
 scalar_t__ XO_STYLE_TEXT ; 
 int XSF_DTRT ; 
 int XSF_INSTANCE ; 
 int XSF_LIST ; 
 scalar_t__ xo_depth_check (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xo_failure (TYPE_2__*,char*,char const*,...) ; 
 int /*<<< orphan*/  xo_free (char*) ; 
 int /*<<< orphan*/  xo_stack_set_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  xo_streq (char const*,char const*) ; 
 char* xo_strndup (char const*,int) ; 
 scalar_t__ xo_style (TYPE_2__*) ; 

__attribute__((used)) static void
xo_depth_change (xo_handle_t *xop, const char *name,
		 int delta, int indent, xo_state_t state, xo_xsf_flags_t flags)
{
    if (xo_style(xop) == XO_STYLE_HTML || xo_style(xop) == XO_STYLE_TEXT)
	indent = 0;

    if (XOF_ISSET(xop, XOF_DTRT))
	flags |= XSF_DTRT;

    if (delta >= 0) {			/* Push operation */
	if (xo_depth_check(xop, xop->xo_depth + delta))
	    return;

	xo_stack_t *xsp = &xop->xo_stack[xop->xo_depth + delta];
	xsp->xs_flags = flags;
	xsp->xs_state = state;
	xo_stack_set_flags(xop);

	if (name == NULL)
	    name = XO_FAILURE_NAME;

	xsp->xs_name = xo_strndup(name, -1);

    } else {			/* Pop operation */
	if (xop->xo_depth == 0) {
	    if (!XOF_ISSET(xop, XOF_IGNORE_CLOSE))
		xo_failure(xop, "close with empty stack: '%s'", name);
	    return;
	}

	xo_stack_t *xsp = &xop->xo_stack[xop->xo_depth];
	if (XOF_ISSET(xop, XOF_WARN)) {
	    const char *top = xsp->xs_name;
	    if (top != NULL && name != NULL && !xo_streq(name, top)) {
		xo_failure(xop, "incorrect close: '%s' .vs. '%s'",
			      name, top);
		return;
	    } 
	    if ((xsp->xs_flags & XSF_LIST) != (flags & XSF_LIST)) {
		xo_failure(xop, "list close on list confict: '%s'",
			      name);
		return;
	    }
	    if ((xsp->xs_flags & XSF_INSTANCE) != (flags & XSF_INSTANCE)) {
		xo_failure(xop, "list close on instance confict: '%s'",
			      name);
		return;
	    }
	}

	if (xsp->xs_name) {
	    xo_free(xsp->xs_name);
	    xsp->xs_name = NULL;
	}
	if (xsp->xs_keys) {
	    xo_free(xsp->xs_keys);
	    xsp->xs_keys = NULL;
	}
    }

    xop->xo_depth += delta;	/* Record new depth */
    xop->xo_indent += indent;
}