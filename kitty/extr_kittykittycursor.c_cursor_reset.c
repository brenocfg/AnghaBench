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
struct TYPE_4__ {int blink; int /*<<< orphan*/  shape; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  NO_CURSOR_SHAPE ; 
 int /*<<< orphan*/  cursor_reset_display_attrs (TYPE_1__*) ; 

void cursor_reset(Cursor *self) {
    cursor_reset_display_attrs(self);
    self->x = 0; self->y = 0;
    self->shape = NO_CURSOR_SHAPE; self->blink = false;
}