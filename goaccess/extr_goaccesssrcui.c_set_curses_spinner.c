#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int curses; int w; int spin_x; int y; int /*<<< orphan*/  x; int /*<<< orphan*/  win; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ GSpinner ;

/* Variables and functions */
 int /*<<< orphan*/  color_progress ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stdscr ; 

void
set_curses_spinner (GSpinner * spinner)
{
  int y, x;
  if (spinner == NULL)
    return;

  getmaxyx (stdscr, y, x);

  spinner->color = color_progress;
  spinner->curses = 1;
  spinner->win = stdscr;
  spinner->x = 0;
  spinner->w = x;
  spinner->spin_x = x - 2;
  spinner->y = y - 1;
}