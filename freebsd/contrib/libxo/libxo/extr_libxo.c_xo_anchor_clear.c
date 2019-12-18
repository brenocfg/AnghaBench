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
struct TYPE_4__ {scalar_t__ xo_anchor_min_width; scalar_t__ xo_anchor_columns; scalar_t__ xo_anchor_offset; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOIF_ANCHOR ; 
 int /*<<< orphan*/  XOIF_CLEAR (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xo_anchor_clear (xo_handle_t *xop)
{
    XOIF_CLEAR(xop, XOIF_ANCHOR);
    xop->xo_anchor_offset = 0;
    xop->xo_anchor_columns = 0;
    xop->xo_anchor_min_width = 0;
}