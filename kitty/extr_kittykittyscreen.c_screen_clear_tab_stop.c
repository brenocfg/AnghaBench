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
struct TYPE_5__ {unsigned int columns; int* tabstops; TYPE_1__* cursor; } ;
struct TYPE_4__ {unsigned int x; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_PREFIX ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

void
screen_clear_tab_stop(Screen *self, unsigned int how) {
    switch(how) {
        case 0:
            if (self->cursor->x < self->columns) self->tabstops[self->cursor->x] = false;
            break;
        case 2:
            break;  // no-op
        case 3:
            for (unsigned int i = 0; i < self->columns; i++) self->tabstops[i] = false;
            break;
        default:
            log_error("%s %s %u", ERROR_PREFIX, "Unsupported clear tab stop mode: ", how);
            break;
    }
}