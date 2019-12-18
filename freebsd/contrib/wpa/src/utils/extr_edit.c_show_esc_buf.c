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
 int /*<<< orphan*/  edit_clear_line () ; 
 int /*<<< orphan*/  edit_redraw () ; 
 int /*<<< orphan*/  printf (char*,char const*,char,int) ; 

__attribute__((used)) static void show_esc_buf(const char *esc_buf, char c, int i)
{
	edit_clear_line();
	printf("\rESC buffer '%s' c='%c' [%d]\n", esc_buf, c, i);
	edit_redraw();
}