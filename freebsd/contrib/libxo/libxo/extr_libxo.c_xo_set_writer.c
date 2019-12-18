#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_write_func_t ;
struct TYPE_5__ {int /*<<< orphan*/  xo_flush; int /*<<< orphan*/  xo_close; int /*<<< orphan*/  xo_write; void* xo_opaque; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  xo_flush_func_t ;
typedef  int /*<<< orphan*/  xo_close_func_t ;

/* Variables and functions */
 TYPE_1__* xo_default (TYPE_1__*) ; 

void
xo_set_writer (xo_handle_t *xop, void *opaque, xo_write_func_t write_func,
	       xo_close_func_t close_func, xo_flush_func_t flush_func)
{
    xop = xo_default(xop);

    xop->xo_opaque = opaque;
    xop->xo_write = write_func;
    xop->xo_close = close_func;
    xop->xo_flush = flush_func;
}