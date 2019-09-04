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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {unsigned int x; unsigned int y; } ;
struct TYPE_8__ {unsigned int columns; unsigned int margin_bottom; TYPE_6__* cursor; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  is_dirty; int /*<<< orphan*/  grman; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  GraphicsCommand ;

/* Variables and functions */
 int /*<<< orphan*/  APC ; 
 int cursor_within_margins (TYPE_1__*) ; 
 char* grman_handle_command (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_ensure_bounds (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  screen_scroll (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

void
screen_handle_graphics_command(Screen *self, const GraphicsCommand *cmd, const uint8_t *payload) {
    unsigned int x = self->cursor->x, y = self->cursor->y;
    const char *response = grman_handle_command(self->grman, cmd, payload, self->cursor, &self->is_dirty, self->cell_size);
    if (response != NULL) write_escape_code_to_child(self, APC, response);
    if (x != self->cursor->x || y != self->cursor->y) {
        bool in_margins = cursor_within_margins(self);
        if (self->cursor->x >= self->columns) { self->cursor->x = 0; self->cursor->y++; }
        if (self->cursor->y > self->margin_bottom) screen_scroll(self, self->cursor->y - self->margin_bottom);
        screen_ensure_bounds(self, false, in_margins);
    }
}