#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mDECOM; } ;
struct TYPE_7__ {unsigned int margin_top; unsigned int margin_bottom; int lines; unsigned int columns; TYPE_1__* cursor; TYPE_2__ modes; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,unsigned int) ; 

void
screen_ensure_bounds(Screen *self, bool force_use_margins/*=false*/, bool in_margins) {
    unsigned int top, bottom;
    if (in_margins && (force_use_margins || self->modes.mDECOM)) {
        top = self->margin_top; bottom = self->margin_bottom;
    } else {
        top = 0; bottom = self->lines - 1;
    }
    self->cursor->x = MIN(self->cursor->x, self->columns - 1);
    self->cursor->y = MAX(top, MIN(self->cursor->y, bottom));
}