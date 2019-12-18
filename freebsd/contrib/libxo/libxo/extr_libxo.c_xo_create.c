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
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
typedef  void* xo_style_t ;
struct TYPE_7__ {void* xo_style; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xo_init_handle (TYPE_1__*) ; 
 TYPE_1__* xo_realloc (int /*<<< orphan*/ *,int) ; 

xo_handle_t *
xo_create (xo_style_t style, xo_xof_flags_t flags)
{
    xo_handle_t *xop = xo_realloc(NULL, sizeof(*xop));

    if (xop) {
	bzero(xop, sizeof(*xop));

	xop->xo_style = style;
	XOF_SET(xop, flags);
	xo_init_handle(xop);
	xop->xo_style = style;	/* Reset style (see LIBXO_OPTIONS) */
    }

    return xop;
}