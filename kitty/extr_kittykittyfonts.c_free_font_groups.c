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

/* Variables and functions */
 int /*<<< orphan*/  del_font_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * font_groups ; 
 scalar_t__ font_groups_capacity ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 size_t num_font_groups ; 

__attribute__((used)) static inline void
free_font_groups() {
    if (font_groups) {
        for (size_t i = 0; i < num_font_groups; i++) del_font_group(font_groups + i);
        free(font_groups); font_groups = NULL;
        font_groups_capacity = 0; num_font_groups = 0;
    }
}