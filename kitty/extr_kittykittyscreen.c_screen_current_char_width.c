#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int columns; scalar_t__ lines; TYPE_1__* cursor; int /*<<< orphan*/  linebuf; } ;
struct TYPE_4__ {int x; scalar_t__ y; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 unsigned long linebuf_char_width_at (int /*<<< orphan*/ ,int,scalar_t__) ; 

unsigned long
screen_current_char_width(Screen *self) {
    unsigned long ans = 1;
    if (self->cursor->x < self->columns - 1 && self->cursor->y < self->lines) {
        ans = linebuf_char_width_at(self->linebuf, self->cursor->x, self->cursor->y);
    }
    return ans;
}