#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double font_sz_in_pts; double logical_dpi_x; double logical_dpi_y; scalar_t__ id; } ;
typedef  TYPE_1__ FontGroup ;

/* Variables and functions */
 int /*<<< orphan*/  add_font_group () ; 
 scalar_t__ font_group_id_counter ; 
 TYPE_1__* font_groups ; 
 int /*<<< orphan*/  initialize_font_group (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 size_t num_font_groups ; 

__attribute__((used)) static inline FontGroup*
font_group_for(double font_sz_in_pts, double logical_dpi_x, double logical_dpi_y) {
    for (size_t i = 0; i < num_font_groups; i++) {
        FontGroup *fg = font_groups + i;
        if (fg->font_sz_in_pts == font_sz_in_pts && fg->logical_dpi_x == logical_dpi_x && fg->logical_dpi_y == logical_dpi_y) return fg;
    }
    add_font_group();
    FontGroup *fg = font_groups + num_font_groups - 1;
    memset(fg, 0, sizeof(FontGroup));
    fg->font_sz_in_pts = font_sz_in_pts;
    fg->logical_dpi_x = logical_dpi_x;
    fg->logical_dpi_y = logical_dpi_y;
    fg->id = ++font_group_id_counter;
    initialize_font_group(fg);
    return fg;
}