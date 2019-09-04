#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ linebuf; scalar_t__ main_linebuf; scalar_t__ alt_linebuf; int is_dirty; int /*<<< orphan*/  selection; int /*<<< orphan*/  main_grman; int /*<<< orphan*/  grman; int /*<<< orphan*/  main_tabstops; int /*<<< orphan*/  tabstops; int /*<<< orphan*/  cursor; int /*<<< orphan*/  alt_grman; int /*<<< orphan*/  alt_tabstops; int /*<<< orphan*/  cell_size; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_CHAR ; 
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 int /*<<< orphan*/  SCROLL_FULL ; 
 int /*<<< orphan*/  cursor_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grman_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_clear (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  screen_history_scroll (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  screen_restore_cursor (TYPE_1__*) ; 
 int /*<<< orphan*/  screen_save_cursor (TYPE_1__*) ; 

void
screen_toggle_screen_buffer(Screen *self) {
    bool to_alt = self->linebuf == self->main_linebuf;
    grman_clear(self->alt_grman, true, self->cell_size);  // always clear the alt buffer graphics to free up resources, since it has to be cleared when switching back to it anyway
    if (to_alt) {
        linebuf_clear(self->alt_linebuf, BLANK_CHAR);
        screen_save_cursor(self);
        self->linebuf = self->alt_linebuf;
        self->tabstops = self->alt_tabstops;
        self->grman = self->alt_grman;
        screen_cursor_position(self, 1, 1);
        cursor_reset(self->cursor);
    } else {
        self->linebuf = self->main_linebuf;
        self->tabstops = self->main_tabstops;
        screen_restore_cursor(self);
        self->grman = self->main_grman;
    }
    screen_history_scroll(self, SCROLL_FULL, false);
    self->is_dirty = true;
    self->selection = EMPTY_SELECTION;
}