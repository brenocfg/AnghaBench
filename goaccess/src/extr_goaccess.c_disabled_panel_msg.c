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
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PANEL_DISABLED ; 
 int /*<<< orphan*/  color_error ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 char* module_to_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static void
disabled_panel_msg (GModule module)
{
  const char *lbl = module_to_label (module);
  int row, col;

  getmaxyx (stdscr, row, col);
  draw_header (stdscr, lbl, ERR_PANEL_DISABLED, row - 1, 0, col, color_error);
}