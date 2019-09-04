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
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  header_win ; 
 int /*<<< orphan*/  main_win ; 
 int /*<<< orphan*/  main_win_height ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  render_screens () ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  term_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_resize (void)
{
  endwin ();
  refresh ();
  werase (header_win);
  werase (main_win);
  werase (stdscr);
  term_size (main_win, &main_win_height);
  refresh ();
  render_screens ();
}