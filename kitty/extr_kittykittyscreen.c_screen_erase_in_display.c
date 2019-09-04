#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int y; } ;
struct TYPE_8__ {int /*<<< orphan*/  line; } ;
struct TYPE_7__ {unsigned int lines; int is_dirty; scalar_t__ scrolled_by; int scroll_changed; int /*<<< orphan*/  historybuf; TYPE_4__* main_linebuf; TYPE_4__* linebuf; int /*<<< orphan*/  selection; int /*<<< orphan*/  columns; TYPE_6__* cursor; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  grman; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_CHAR ; 
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 int /*<<< orphan*/  grman_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  historybuf_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_apply_cursor (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  line_clear_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  screen_erase_in_line (TYPE_1__*,unsigned int,int) ; 

void
screen_erase_in_display(Screen *self, unsigned int how, bool private) {
    /* Erases display in a specific way.

        :param int how: defines the way the screen should be erased:

            * ``0`` -- Erases from cursor to end of screen, including
              cursor position.
            * ``1`` -- Erases from beginning of screen to cursor,
              including cursor position.
            * ``2`` -- Erases complete display. All lines are erased
              and changed to single-width. Cursor does not move.
            * ``3`` -- Erase complete display and scrollback buffer as well.
        :param bool private: when ``True`` character attributes are left unchanged
    */
    unsigned int a, b;
    switch(how) {
        case 0:
            a = self->cursor->y + 1; b = self->lines; break;
        case 1:
            a = 0; b = self->cursor->y; break;
        case 2:
        case 3:
            grman_clear(self->grman, how == 3, self->cell_size);
            a = 0; b = self->lines; break;
        default:
            return;
    }
    if (b > a) {
        for (unsigned int i=a; i < b; i++) {
            linebuf_init_line(self->linebuf, i);
            if (private) {
                line_clear_text(self->linebuf->line, 0, self->columns, BLANK_CHAR);
            } else {
                line_apply_cursor(self->linebuf->line, self->cursor, 0, self->columns, true);
            }
            linebuf_mark_line_dirty(self->linebuf, i);
        }
        self->is_dirty = true;
        self->selection = EMPTY_SELECTION;
    }
    if (how != 2) {
        screen_erase_in_line(self, how, private);
    }
    if (how == 3 && self->linebuf == self->main_linebuf) {
        historybuf_clear(self->historybuf);
        if (self->scrolled_by != 0) {
            self->scrolled_by = 0;
            self->scroll_changed = true;
        }
    }
}