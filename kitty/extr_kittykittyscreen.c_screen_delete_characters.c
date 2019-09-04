#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int y; unsigned int x; } ;
struct TYPE_7__ {int /*<<< orphan*/  line; } ;
struct TYPE_6__ {unsigned int margin_top; unsigned int margin_bottom; int is_dirty; int /*<<< orphan*/  selection; TYPE_5__* cursor; TYPE_3__* linebuf; scalar_t__ columns; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 unsigned int MIN (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  left_shift_line (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  line_apply_cursor (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_3__*,unsigned int) ; 
 scalar_t__ selection_has_screen_line (int /*<<< orphan*/ *,unsigned int) ; 

void
screen_delete_characters(Screen *self, unsigned int count) {
    // Delete characters, later characters are moved left
    unsigned int top = self->margin_top, bottom = self->margin_bottom;
    if (count == 0) count = 1;
    if (top <= self->cursor->y && self->cursor->y <= bottom) {
        unsigned int x = self->cursor->x;
        unsigned int num = MIN(self->columns - x, count);
        linebuf_init_line(self->linebuf, self->cursor->y);
        left_shift_line(self->linebuf->line, x, num);
        line_apply_cursor(self->linebuf->line, self->cursor, self->columns - num, num, true);
        linebuf_mark_line_dirty(self->linebuf, self->cursor->y);
        self->is_dirty = true;
        if (selection_has_screen_line(&self->selection, self->cursor->y)) self->selection = EMPTY_SELECTION;
    }
}