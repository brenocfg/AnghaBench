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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int MIN_HEIGHT ; 
 int MIN_WIDTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wbkgd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdscr ; 

void
init_windows (WINDOW ** header_win, WINDOW ** main_win)
{
  int row = 0, col = 0;

  /* init standard screen */
  getmaxyx (stdscr, row, col);
  if (row < MIN_HEIGHT || col < MIN_WIDTH)
    FATAL ("Minimum screen size - 0 columns by 7 lines");

  /* init header screen */
  *header_win = newwin (6, col, 0, 0);
  keypad (*header_win, TRUE);
  if (*header_win == NULL)
    FATAL ("Unable to allocate memory for header_win.");

  /* init main screen */
  *main_win = newwin (row - 8, col, 7, 0);
  keypad (*main_win, TRUE);
  if (*main_win == NULL)
    FATAL ("Unable to allocate memory for main_win.");
  set_wbkgd (*main_win, *header_win);
}