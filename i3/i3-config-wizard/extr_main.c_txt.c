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
typedef  int /*<<< orphan*/  i3String ;
typedef  int /*<<< orphan*/  color_t ;

/* Variables and functions */
 int TEXT_PADDING ; 
 int WIN_WIDTH ; 
 int col_x (int) ; 
 int /*<<< orphan*/  draw_util_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_utf8 (char*) ; 
 int row_y (int) ; 
 int /*<<< orphan*/  surface ; 

__attribute__((used)) static void txt(int col, int row, char *text, color_t fg, color_t bg) {
    int x = col_x(col);
    int y = row_y(row);
    i3String *string = i3string_from_utf8(text);
    draw_util_text(string, &surface, fg, bg, x, y, WIN_WIDTH - x - TEXT_PADDING);
    i3string_free(string);
}