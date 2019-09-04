#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int margin_top; unsigned int margin_bottom; int is_dirty; int /*<<< orphan*/  selection; TYPE_1__* cursor; int /*<<< orphan*/  linebuf; } ;
struct TYPE_5__ {unsigned int y; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 int /*<<< orphan*/  linebuf_delete_lines (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  screen_carriage_return (TYPE_2__*) ; 

void
screen_delete_lines(Screen *self, unsigned int count) {
    unsigned int top = self->margin_top, bottom = self->margin_bottom;
    if (count == 0) count = 1;
    if (top <= self->cursor->y && self->cursor->y <= bottom) {
        linebuf_delete_lines(self->linebuf, count, self->cursor->y, bottom);
        self->is_dirty = true;
        self->selection = EMPTY_SELECTION;
        screen_carriage_return(self);
    }
}