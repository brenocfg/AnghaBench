#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_active; scalar_t__ ynum; scalar_t__ xstart; scalar_t__ xnum; int /*<<< orphan*/  cpu_cells; int /*<<< orphan*/  gpu_cells; } ;
struct TYPE_8__ {scalar_t__ lines; int is_dirty; TYPE_2__ overlay_line; int /*<<< orphan*/  linebuf; TYPE_1__* cursor; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ Screen ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/  line_reset_cells (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * range_line_ (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void
deactivate_overlay_line(Screen *self) {
    if (self->overlay_line.is_active && self->overlay_line.xnum && self->overlay_line.ynum < self->lines) {
        Line *line = range_line_(self, self->overlay_line.ynum);
        line_reset_cells(line, self->overlay_line.xstart, self->overlay_line.xnum, self->overlay_line.gpu_cells, self->overlay_line.cpu_cells);
        if (self->cursor->y == self->overlay_line.ynum) self->cursor->x = self->overlay_line.xstart;
        self->is_dirty = true;
        linebuf_mark_line_dirty(self->linebuf, self->overlay_line.ynum);
    }
    self->overlay_line.is_active = false;
    self->overlay_line.ynum = 0;
    self->overlay_line.xnum = 0;
    self->overlay_line.xstart = 0;
}