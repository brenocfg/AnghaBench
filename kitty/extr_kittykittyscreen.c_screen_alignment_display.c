#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int ynum; int /*<<< orphan*/  xnum; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {TYPE_4__* linebuf; scalar_t__ lines; scalar_t__ margin_bottom; scalar_t__ margin_top; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  line_clear_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_1__*,int,int) ; 

void
screen_alignment_display(Screen *self) {
    // https://www.vt100.net/docs/vt510-rm/DECALN.html
    screen_cursor_position(self, 1, 1);
    self->margin_top = 0; self->margin_bottom = self->lines - 1;
    for (unsigned int y = 0; y < self->linebuf->ynum; y++) {
        linebuf_init_line(self->linebuf, y);
        line_clear_text(self->linebuf->line, 0, self->linebuf->xnum, 'E');
        linebuf_mark_line_dirty(self->linebuf, y);
    }
}