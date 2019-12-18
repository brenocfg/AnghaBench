#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int xb_curp; } ;
struct TYPE_6__ {TYPE_2__ xo_data; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  TYPE_2__ xo_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int,char,int) ; 
 int /*<<< orphan*/  xo_buf_has_room (TYPE_2__*,int) ; 
 int xo_indent (TYPE_1__*) ; 

__attribute__((used)) static void
xo_buf_indent (xo_handle_t *xop, int indent)
{
    xo_buffer_t *xbp = &xop->xo_data;

    if (indent <= 0)
	indent = xo_indent(xop);

    if (!xo_buf_has_room(xbp, indent))
	return;

    memset(xbp->xb_curp, ' ', indent);
    xbp->xb_curp += indent;
}