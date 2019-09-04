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
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_6__ {TYPE_1__* cursor; int /*<<< orphan*/  margin_bottom; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 unsigned int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_index (TYPE_2__*) ; 

void
screen_scroll_until_cursor(Screen *self) {
    unsigned int num_lines_to_scroll = MIN(self->margin_bottom, self->cursor->y + 1);
    index_type y = self->cursor->y;
    self->cursor->y = self->margin_bottom;
    while (num_lines_to_scroll--) screen_index(self);
    self->cursor->y = y;
}