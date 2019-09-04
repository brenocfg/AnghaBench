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
 int MAX_HEIGHT_FOOTER ; 
 int MAX_HEIGHT_HEADER ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wresize (int /*<<< orphan*/ *,int,int) ; 

void
term_size (WINDOW * main_win, int *main_win_height)
{
  int term_h = 0, term_w = 0;

  getmaxyx (stdscr, term_h, term_w);

  *main_win_height = term_h - (MAX_HEIGHT_HEADER + MAX_HEIGHT_FOOTER);
  wresize (main_win, *main_win_height, term_w);
  wmove (main_win, *main_win_height, 0);
}