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
struct symtab_and_line {int /*<<< orphan*/  symtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_WIN ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  tui_add_win_to_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_locator_filename (char const*) ; 
 int /*<<< orphan*/  tui_update_source_windows_with_line (int /*<<< orphan*/ ,int) ; 

void
tui_show_source (const char *file, int line)
{
  struct symtab_and_line cursal = get_current_source_symtab_and_line ();
  /* make sure that the source window is displayed */
  tui_add_win_to_layout (SRC_WIN);

  tui_update_source_windows_with_line (cursal.symtab, line);
  tui_update_locator_filename (file);
}