#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ is_active; } ;
struct TYPE_15__ {scalar_t__ linebuf; scalar_t__ alt_linebuf; int is_dirty; int /*<<< orphan*/  selection; int /*<<< orphan*/  cursor; int /*<<< orphan*/  columns; int /*<<< orphan*/  alt_tabstops; int /*<<< orphan*/  main_tabstops; scalar_t__ lines; scalar_t__ margin_bottom; scalar_t__ margin_top; TYPE_3__* color_profile; int /*<<< orphan*/  modes; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  grman; int /*<<< orphan*/  historybuf; TYPE_1__ overlay_line; } ;
struct TYPE_13__ {scalar_t__ highlight_bg; scalar_t__ highlight_fg; scalar_t__ cursor_color; scalar_t__ default_bg; scalar_t__ default_fg; } ;
struct TYPE_14__ {TYPE_2__ overridden; } ;
typedef  TYPE_4__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_CHAR ; 
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 int /*<<< orphan*/  RESET_CHARSETS ; 
 int /*<<< orphan*/  cursor_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deactivate_overlay_line (TYPE_4__*) ; 
 int /*<<< orphan*/  empty_modes ; 
 int /*<<< orphan*/  grman_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  historybuf_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tabstops (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_clear (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  screen_normal_keypad_mode (TYPE_4__*) ; 
 int /*<<< orphan*/  screen_toggle_screen_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  set_color_table_color (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dynamic_color (TYPE_4__*,int,int /*<<< orphan*/ *) ; 

void
screen_reset(Screen *self) {
    if (self->linebuf == self->alt_linebuf) screen_toggle_screen_buffer(self);
    if (self->overlay_line.is_active) deactivate_overlay_line(self);
    linebuf_clear(self->linebuf, BLANK_CHAR);
    historybuf_clear(self->historybuf);
    grman_clear(self->grman, false, self->cell_size);
    self->modes = empty_modes;
#define R(name) self->color_profile->overridden.name = 0
    R(default_fg); R(default_bg); R(cursor_color); R(highlight_fg); R(highlight_bg);
#undef R
    RESET_CHARSETS;
    self->margin_top = 0; self->margin_bottom = self->lines - 1;
    screen_normal_keypad_mode(self);
    init_tabstops(self->main_tabstops, self->columns);
    init_tabstops(self->alt_tabstops, self->columns);
    cursor_reset(self->cursor);
    self->is_dirty = true;
    self->selection = EMPTY_SELECTION;
    screen_cursor_position(self, 1, 1);
    set_dynamic_color(self, 110, NULL);
    set_dynamic_color(self, 111, NULL);
    set_color_table_color(self, 104, NULL);
}