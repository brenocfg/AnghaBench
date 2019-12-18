#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
typedef  int /*<<< orphan*/  xo_style_t ;
struct TYPE_4__ {int /*<<< orphan*/  xo_flush; int /*<<< orphan*/  xo_close; int /*<<< orphan*/  xo_write; int /*<<< orphan*/ * xo_opaque; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  xo_close_file ; 
 TYPE_1__* xo_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_flush_file ; 
 int /*<<< orphan*/  xo_write_to_file ; 

xo_handle_t *
xo_create_to_file (FILE *fp, xo_style_t style, xo_xof_flags_t flags)
{
    xo_handle_t *xop = xo_create(style, flags);

    if (xop) {
	xop->xo_opaque = fp;
	xop->xo_write = xo_write_to_file;
	xop->xo_close = xo_close_file;
	xop->xo_flush = xo_flush_file;
    }

    return xop;
}