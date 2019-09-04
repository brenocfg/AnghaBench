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
struct TYPE_8__ {unsigned int x; int /*<<< orphan*/  y; } ;
struct TYPE_7__ {int /*<<< orphan*/  line; } ;
struct TYPE_6__ {unsigned int columns; int is_dirty; TYPE_5__* cursor; TYPE_3__* linebuf; int /*<<< orphan*/  selection; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_CHAR ; 
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 int /*<<< orphan*/  line_apply_cursor (int /*<<< orphan*/ ,TYPE_5__*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  line_clear_text (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ selection_has_screen_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
screen_erase_in_line(Screen *self, unsigned int how, bool private) {
    /*Erases a line in a specific way.

        :param int how: defines the way the line should be erased in:

            * ``0`` -- Erases from cursor to end of line, including cursor
              position.
            * ``1`` -- Erases from beginning of line to cursor,
              including cursor position.
            * ``2`` -- Erases complete line.
        :param bool private: when ``True`` character attributes are left
                             unchanged.
        */
    unsigned int s = 0, n = 0;
    switch(how) {
        case 0:
            s = self->cursor->x;
            n = self->columns - self->cursor->x;
            break;
        case 1:
            n = self->cursor->x + 1;
            break;
        case 2:
            n = self->columns;
            break;
        default:
            break;
    }
    if (n > 0) {
        linebuf_init_line(self->linebuf, self->cursor->y);
        if (private) {
            line_clear_text(self->linebuf->line, s, n, BLANK_CHAR);
        } else {
            line_apply_cursor(self->linebuf->line, self->cursor, s, n, true);
        }
        self->is_dirty = true;
        if (selection_has_screen_line(&self->selection, self->cursor->y)) self->selection = EMPTY_SELECTION;
        linebuf_mark_line_dirty(self->linebuf, self->cursor->y);
    }
}