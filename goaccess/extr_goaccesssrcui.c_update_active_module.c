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
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_2__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_ACTIVE_LABEL ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 char* T_ACTIVE_PANEL ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* get_color (int /*<<< orphan*/ ) ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 char* module_to_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  stdscr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 
 char* xmalloc (scalar_t__) ; 

void
update_active_module (WINDOW * header_win, GModule current)
{
  GColors *color = get_color (COLOR_ACTIVE_LABEL);
  const char *module = module_to_label (current);
  int col = getmaxx (stdscr);

  char *lbl = xmalloc (snprintf (NULL, 0, T_ACTIVE_PANEL, module) + 1);
  sprintf (lbl, T_ACTIVE_PANEL, module);

  wmove (header_win, 0, 30);

  wattron (header_win, color->attr | COLOR_PAIR (color->pair->idx));
  mvwprintw (header_win, 0, col - strlen (lbl) - 1, "%s", lbl);
  wattroff (header_win, color->attr | COLOR_PAIR (color->pair->idx));

  wrefresh (header_win);

  free (lbl);
}