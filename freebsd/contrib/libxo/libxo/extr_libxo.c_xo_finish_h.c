#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_ssize_t ;
struct TYPE_14__ {int /*<<< orphan*/  xo_stack; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 scalar_t__ XOF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_NO_CLOSE ; 
 int /*<<< orphan*/  XOF_NO_TOP ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOIF_CLEAR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_MADE_OUTPUT ; 
 int /*<<< orphan*/  XOIF_TOP_EMITTED ; 
 int /*<<< orphan*/  XO_OP_FINISH ; 
#define  XO_STYLE_ENCODER 129 
#define  XO_STYLE_JSON 128 
 TYPE_1__* xo_default (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_do_close_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_encoder_handle (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_flush_h (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_indent (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_printf (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ,char*,char const*) ; 
 int xo_style (TYPE_1__*) ; 

xo_ssize_t
xo_finish_h (xo_handle_t *xop)
{
    const char *open_if_empty = "";
    xop = xo_default(xop);

    if (!XOF_ISSET(xop, XOF_NO_CLOSE))
	xo_do_close_all(xop, xop->xo_stack);

    switch (xo_style(xop)) {
    case XO_STYLE_JSON:
	if (!XOF_ISSET(xop, XOF_NO_TOP)) {
	    const char *pre_nl = XOF_ISSET(xop, XOF_PRETTY) ? "\n" : "";

	    if (XOIF_ISSET(xop, XOIF_TOP_EMITTED))
		XOIF_CLEAR(xop, XOIF_TOP_EMITTED); /* Turn off before output */
	    else if (!XOIF_ISSET(xop, XOIF_MADE_OUTPUT)) {
		open_if_empty = "{ ";
		pre_nl = "";
	    }

	    xo_printf(xop, "%s%*s%s}\n",
		      pre_nl, xo_indent(xop), "", open_if_empty);
	}
	break;

    case XO_STYLE_ENCODER:
	xo_encoder_handle(xop, XO_OP_FINISH, NULL, NULL, 0);
	break;
    }

    return xo_flush_h(xop);
}