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
struct TYPE_6__ {unsigned int scrolled_by; unsigned int lines; unsigned int columns; } ;
struct TYPE_5__ {unsigned int x; int y; } ;
typedef  TYPE_1__ SelectionBoundary ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */

__attribute__((used)) static inline void
selection_coord(Screen *self, unsigned int x, unsigned int y, unsigned int ydelta, SelectionBoundary *ans) {
    if (y + self->scrolled_by < ydelta) {
        ans->x = 0; ans->y = 0;
    } else {
        y = y - ydelta + self->scrolled_by;
        if (y >= self->lines) {
            ans->x = self->columns - 1; ans->y = self->lines - 1;
        } else {
            ans->x = x; ans->y = y;
        }
    }
}