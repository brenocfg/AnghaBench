#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FontGroup ;

/* Variables and functions */
 scalar_t__ font_group_is_unused (scalar_t__) ; 
 scalar_t__ font_groups ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 size_t num_font_groups ; 
 int /*<<< orphan*/  restore_window_font_groups () ; 
 int /*<<< orphan*/  save_window_font_groups () ; 

__attribute__((used)) static inline void
trim_unused_font_groups() {
    save_window_font_groups();
    size_t i = 0;
    while (i < num_font_groups) {
        if (font_group_is_unused(font_groups + i)) {
            size_t num_to_right = (--num_font_groups) - i;
            if (!num_to_right) break;
            memmove(font_groups + i, font_groups + 1 + i, num_to_right * sizeof(FontGroup));
        } else i++;
    }
    restore_window_font_groups();
}