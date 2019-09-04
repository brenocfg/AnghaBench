#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  linebuf; scalar_t__ lines; scalar_t__ margin_bottom; scalar_t__ margin_top; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  linebuf_clear (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_1__*,int,int) ; 

void
screen_align(Screen *self) {
    self->margin_top = 0; self->margin_bottom = self->lines - 1;
    screen_cursor_position(self, 1, 1);
    linebuf_clear(self->linebuf, 'E');
}