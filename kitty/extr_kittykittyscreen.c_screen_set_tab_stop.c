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
struct TYPE_5__ {size_t columns; int* tabstops; TYPE_1__* cursor; } ;
struct TYPE_4__ {size_t x; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */

void
screen_set_tab_stop(Screen *self) {
    if (self->cursor->x < self->columns)
        self->tabstops[self->cursor->x] = true;
}