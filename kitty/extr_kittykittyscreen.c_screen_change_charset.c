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
typedef  int uint32_t ;
struct TYPE_3__ {int current_charset; int /*<<< orphan*/  g1_charset; int /*<<< orphan*/  g_charset; int /*<<< orphan*/  g0_charset; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */

void
screen_change_charset(Screen *self, uint32_t which) {
    switch(which) {
        case 0:
            self->current_charset = 0;
            self->g_charset = self->g0_charset;
            break;
        case 1:
            self->current_charset = 1;
            self->g_charset = self->g1_charset;
            break;
    }
}