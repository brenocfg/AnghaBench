#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int margin_top; unsigned int margin_bottom; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_UP ; 

void
screen_scroll(Screen *self, unsigned int count) {
    // Scroll the screen up by count lines, not moving the cursor
    unsigned int top = self->margin_top, bottom = self->margin_bottom;
    while (count > 0) {
        count--;
        INDEX_UP;
    }
}