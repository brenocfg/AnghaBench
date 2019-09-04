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
struct TYPE_6__ {int lines; } ;
struct TYPE_5__ {scalar_t__ start_scrolled_by; scalar_t__ end_scrolled_by; scalar_t__ start_x; scalar_t__ end_x; scalar_t__ start_y; scalar_t__ end_y; } ;
typedef  TYPE_1__ Selection ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */

__attribute__((used)) static inline void
index_selection(Screen *self, Selection *s, bool up) {
    if (s->start_scrolled_by == s->end_scrolled_by && s->start_x == s->end_x && s->start_y == s->end_y) return;
    if (up) {
        if (s->start_y == 0) s->start_scrolled_by += 1;
        else s->start_y--;
        if (s->end_y == 0) s->end_scrolled_by += 1;
        else s->end_y--;
    } else {
        if (s->start_y >= self->lines - 1) s->start_scrolled_by -= 1;
        else s->start_y++;
        if (s->end_y >= self->lines - 1) s->end_scrolled_by -= 1;
        else s->end_y++;
    }
}