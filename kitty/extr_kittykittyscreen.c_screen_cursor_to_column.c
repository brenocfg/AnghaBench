#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cursor; } ;
struct TYPE_6__ {unsigned int x; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int MAX (unsigned int,int) ; 
 int /*<<< orphan*/  cursor_within_margins (TYPE_2__*) ; 
 int /*<<< orphan*/  screen_ensure_bounds (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

void
screen_cursor_to_column(Screen *self, unsigned int column) {
    unsigned int x = MAX(column, 1) - 1;
    if (x != self->cursor->x) {
        self->cursor->x = x;
        screen_ensure_bounds(self, false, cursor_within_margins(self));
    }
}