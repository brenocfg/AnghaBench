#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int xo_xsf_flags_t ;
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
typedef  int xo_state_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_NOT_FIRST ; 
 int XSF_LIST ; 
 int XSF_NOT_FIRST ; 
#define  XSS_CLOSE_INSTANCE 131 
#define  XSS_CLOSE_LIST 130 
#define  XSS_OPEN_INSTANCE 129 
#define  XSS_OPEN_LIST 128 
 int /*<<< orphan*/ * xo_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_depth_change (int /*<<< orphan*/ *,char const*,int,int,int const,int) ; 
 int /*<<< orphan*/  xo_do_close_instance (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xo_do_close_list (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xo_do_open_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xo_do_open_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int xo_stack_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_stack_set_flags (int /*<<< orphan*/ *) ; 

void
xo_explicit_transition (xo_handle_t *xop, xo_state_t new_state,
			const char *name, xo_xof_flags_t flags)
{
    xo_xsf_flags_t xsf_flags;

    xop = xo_default(xop);

    switch (new_state) {

    case XSS_OPEN_LIST:
	xo_do_open_list(xop, flags, name);
	break;

    case XSS_OPEN_INSTANCE:
	xo_do_open_instance(xop, flags, name);
	break;

    case XSS_CLOSE_INSTANCE:
	xo_depth_change(xop, name, 1, 1, XSS_OPEN_INSTANCE,
			xo_stack_flags(flags));
	xo_stack_set_flags(xop);
	xo_do_close_instance(xop, name);
	break;

    case XSS_CLOSE_LIST:
	xsf_flags = XOF_ISSET(xop, XOF_NOT_FIRST) ? XSF_NOT_FIRST : 0;

	xo_depth_change(xop, name, 1, 1, XSS_OPEN_LIST,
			XSF_LIST | xsf_flags | xo_stack_flags(flags));
	xo_do_close_list(xop, name);
	break;
    }
}