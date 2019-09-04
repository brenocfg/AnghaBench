#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
struct TYPE_6__ {size_t ynum; int continued; int has_dirty_text; int /*<<< orphan*/  xnum; } ;
struct TYPE_5__ {int* line_attrs; int /*<<< orphan*/ * line_map; TYPE_4__* line; int /*<<< orphan*/  xnum; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

void
linebuf_init_line(LineBuf *self, index_type idx) {
    self->line->ynum = idx;
    self->line->xnum = self->xnum;
    self->line->continued = self->line_attrs[idx] & CONTINUED_MASK ? true : false;
    self->line->has_dirty_text = self->line_attrs[idx] & TEXT_DIRTY_MASK ? true : false;
    init_line(self, self->line, self->line_map[idx]);
}