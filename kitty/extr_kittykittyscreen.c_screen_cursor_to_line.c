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
struct TYPE_6__ {TYPE_1__* cursor; } ;
struct TYPE_5__ {scalar_t__ x; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  screen_cursor_position (TYPE_2__*,unsigned int,scalar_t__) ; 

void
screen_cursor_to_line(Screen *self, unsigned int line) {
    screen_cursor_position(self, line, self->cursor->x + 1);
}