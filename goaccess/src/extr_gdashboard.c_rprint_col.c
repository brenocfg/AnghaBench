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
struct TYPE_5__ {int attr; TYPE_1__* pair; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ GColors ;

/* Variables and functions */
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLOR_PANEL_COLS ; 
 scalar_t__ DASH_SPACE ; 
 TYPE_2__* get_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char const*,int,char const*) ; 
 int /*<<< orphan*/  print_horizontal_dash (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
rprint_col (WINDOW * win, int y, int *x, int len, const char *fmt,
            const char *str)
{
  GColors *color = get_color (COLOR_PANEL_COLS);

  wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
  mvwprintw (win, y, *x, fmt, len, str);
  print_horizontal_dash (win, y + 1, *x, len);
  wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));

  *x += len + DASH_SPACE;
}