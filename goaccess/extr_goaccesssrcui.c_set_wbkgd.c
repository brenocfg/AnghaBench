#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {TYPE_1__* pair; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BG ; 
 int /*<<< orphan*/  COLOR_PAIR (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  wbkgd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
set_wbkgd (WINDOW * main_win, WINDOW * header_win)
{
  GColors *color = get_color (COLOR_BG);

  /* background colors */
  wbkgd (main_win, COLOR_PAIR (color->pair->idx));
  wbkgd (header_win, COLOR_PAIR (color->pair->idx));
  wbkgd (stdscr, COLOR_PAIR (color->pair->idx));
  wrefresh (main_win);
}