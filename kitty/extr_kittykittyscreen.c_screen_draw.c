#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {unsigned int x; size_t y; } ;
struct TYPE_12__ {int /*<<< orphan*/  line; int /*<<< orphan*/ * line_attrs; } ;
struct TYPE_10__ {scalar_t__ mIRM; scalar_t__ mDECAWM; } ;
struct TYPE_11__ {int* g_charset; unsigned int columns; int is_dirty; TYPE_8__* cursor; TYPE_6__* linebuf; int /*<<< orphan*/  selection; TYPE_1__ modes; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUED_MASK ; 
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  draw_combining_char (TYPE_2__*,int) ; 
 int is_combining_char (int) ; 
 scalar_t__ is_ignored_char (int) ; 
 int /*<<< orphan*/  line_right_shift (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  line_set_char (int /*<<< orphan*/ ,unsigned int,int,int,TYPE_8__*,int) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  screen_carriage_return (TYPE_2__*) ; 
 int /*<<< orphan*/  screen_linefeed (TYPE_2__*) ; 
 scalar_t__ selection_has_screen_line (int /*<<< orphan*/ *,size_t) ; 
 int wcwidth_std (int) ; 

void
screen_draw(Screen *self, uint32_t och) {
    if (is_ignored_char(och)) return;
    uint32_t ch = och < 256 ? self->g_charset[och] : och;
    bool is_cc = is_combining_char(ch);
    if (UNLIKELY(is_cc)) {
        draw_combining_char(self, ch);
        return;
    }
    int char_width = wcwidth_std(ch);
    if (UNLIKELY(char_width < 1)) {
        if (char_width == 0) return;
        char_width = 1;
    }
    if (UNLIKELY(self->columns - self->cursor->x < (unsigned int)char_width)) {
        if (self->modes.mDECAWM) {
            screen_carriage_return(self);
            screen_linefeed(self);
            self->linebuf->line_attrs[self->cursor->y] |= CONTINUED_MASK;
        } else {
            self->cursor->x = self->columns - char_width;
        }
    }

    linebuf_init_line(self->linebuf, self->cursor->y);
    if (self->modes.mIRM) {
        line_right_shift(self->linebuf->line, self->cursor->x, char_width);
    }
    line_set_char(self->linebuf->line, self->cursor->x, ch, char_width, self->cursor, false);
    self->cursor->x++;
    if (char_width == 2) {
        line_set_char(self->linebuf->line, self->cursor->x, 0, 0, self->cursor, true);
        self->cursor->x++;
    }
    self->is_dirty = true;
    if (selection_has_screen_line(&self->selection, self->cursor->y)) self->selection = EMPTY_SELECTION;
    linebuf_mark_line_dirty(self->linebuf, self->cursor->y);
}