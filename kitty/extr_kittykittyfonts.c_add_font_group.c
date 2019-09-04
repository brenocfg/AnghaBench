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
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * font_groups ; 
 int font_groups_capacity ; 
 int num_font_groups ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  restore_window_font_groups () ; 
 int /*<<< orphan*/  save_window_font_groups () ; 
 int /*<<< orphan*/  trim_unused_font_groups () ; 

__attribute__((used)) static inline void
add_font_group() {
    if (num_font_groups) trim_unused_font_groups();
    if (num_font_groups >= font_groups_capacity) {
        save_window_font_groups();
        font_groups_capacity += 5;
        font_groups = realloc(font_groups, sizeof(FontGroup) * font_groups_capacity);
        if (font_groups == NULL) fatal("Out of memory creating a new font group");
        restore_window_font_groups();
    }
    num_font_groups++;
}