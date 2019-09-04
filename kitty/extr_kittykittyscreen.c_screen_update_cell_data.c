#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_16__ {unsigned int count; TYPE_2__* line; } ;
struct TYPE_15__ {TYPE_2__* line; } ;
struct TYPE_14__ {scalar_t__ y; } ;
struct TYPE_13__ {scalar_t__ has_dirty_text; } ;
struct TYPE_12__ {unsigned int history_line_added_count; int is_dirty; int scrolled_by; int scroll_changed; unsigned int lines; scalar_t__ last_rendered_cursor_y; int /*<<< orphan*/  url_range; TYPE_7__* linebuf; int /*<<< orphan*/  disable_ligatures; TYPE_6__* cursor; TYPE_9__* historybuf; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 scalar_t__ MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  historybuf_init_line (TYPE_9__*,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  historybuf_mark_line_clean (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  linebuf_mark_line_clean (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  render_line (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_reset_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  update_line_data (TYPE_2__*,scalar_t__,void*) ; 

void
screen_update_cell_data(Screen *self, void *address, FONTS_DATA_HANDLE fonts_data, bool cursor_has_moved) {
    unsigned int history_line_added_count = self->history_line_added_count;
    index_type lnum;
    bool was_dirty = self->is_dirty;
    if (self->scrolled_by) self->scrolled_by = MIN(self->scrolled_by + history_line_added_count, self->historybuf->count);
    screen_reset_dirty(self);
    self->scroll_changed = false;
    for (index_type y = 0; y < MIN(self->lines, self->scrolled_by); y++) {
        lnum = self->scrolled_by - 1 - y;
        historybuf_init_line(self->historybuf, lnum, self->historybuf->line);
        if (self->historybuf->line->has_dirty_text) {
            render_line(fonts_data, self->historybuf->line, lnum, self->cursor, self->disable_ligatures);
            historybuf_mark_line_clean(self->historybuf, lnum);
        }
        update_line_data(self->historybuf->line, y, address);
    }
    for (index_type y = self->scrolled_by; y < self->lines; y++) {
        lnum = y - self->scrolled_by;
        linebuf_init_line(self->linebuf, lnum);
        if (self->linebuf->line->has_dirty_text ||
            (cursor_has_moved && (self->cursor->y == lnum || self->last_rendered_cursor_y == lnum))) {
            render_line(fonts_data, self->linebuf->line, lnum, self->cursor, self->disable_ligatures);
            linebuf_mark_line_clean(self->linebuf, lnum);
        }
        update_line_data(self->linebuf->line, y, address);
    }
    if (was_dirty) {
        self->url_range = EMPTY_SELECTION;
    }
}