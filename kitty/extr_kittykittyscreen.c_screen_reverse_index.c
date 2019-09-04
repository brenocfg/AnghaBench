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
struct TYPE_6__ {unsigned int margin_top; unsigned int margin_bottom; TYPE_1__* cursor; } ;
struct TYPE_5__ {unsigned int y; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_DOWN ; 
 int /*<<< orphan*/  screen_cursor_up (TYPE_2__*,int,int,int) ; 

void
screen_reverse_index(Screen *self) {
    // Move cursor up one line, scrolling screen if needed
    unsigned int top = self->margin_top, bottom = self->margin_bottom;
    if (self->cursor->y == top) {
        INDEX_DOWN;
    } else screen_cursor_up(self, 1, false, -1);
}