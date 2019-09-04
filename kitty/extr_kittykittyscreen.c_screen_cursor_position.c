#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mDECOM; } ;
struct TYPE_9__ {TYPE_1__* cursor; int /*<<< orphan*/  margin_bottom; scalar_t__ margin_top; TYPE_2__ modes; } ;
struct TYPE_7__ {unsigned int x; unsigned int y; } ;
typedef  TYPE_3__ Screen ;

/* Variables and functions */
 unsigned int MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (unsigned int,int /*<<< orphan*/ ) ; 
 int cursor_within_margins (TYPE_3__*) ; 
 int /*<<< orphan*/  screen_ensure_bounds (TYPE_3__*,int,int) ; 

void
screen_cursor_position(Screen *self, unsigned int line, unsigned int column) {
    bool in_margins = cursor_within_margins(self);
    line = (line == 0 ? 1 : line) - 1;
    column = (column == 0 ? 1: column) - 1;
    if (self->modes.mDECOM) {
        line += self->margin_top;
        line = MAX(self->margin_top, MIN(line, self->margin_bottom));
    }
    self->cursor->x = column; self->cursor->y = line;
    screen_ensure_bounds(self, false, in_margins);
}