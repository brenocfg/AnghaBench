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
struct TYPE_3__ {unsigned int columns; unsigned int lines; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */

__attribute__((used)) static inline bool
is_selection_empty(Screen *self, unsigned int start_x, unsigned int start_y, unsigned int end_x, unsigned int end_y) {
    return (start_x >= self->columns || start_y >= self->lines || end_x >= self->columns || end_y >= self->lines || (start_x == end_x && start_y == end_y)) ? true : false;
}