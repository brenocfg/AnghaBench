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
struct TYPE_3__ {int start_scrolled_by; int end_scrolled_by; scalar_t__ start_x; scalar_t__ end_x; scalar_t__ start_y; scalar_t__ end_y; } ;
typedef  TYPE_1__ Selection ;

/* Variables and functions */

__attribute__((used)) static inline bool
selection_has_screen_line(Selection *s, int y) {
    if (s->start_scrolled_by == s->end_scrolled_by && s->start_x == s->end_x && s->start_y == s->end_y) return false;
    int top = (int)s->start_y - s->start_scrolled_by;
    int bottom = (int)s->end_y - s->end_scrolled_by;
    return top <= y && y <= bottom;
}