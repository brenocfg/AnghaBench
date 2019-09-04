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
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,char const*) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_overall_field (WINDOW * win, const char *s, int y, int x,
                      GColors * color)
{
  wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
  mvwprintw (win, y, x, "%s", s);
  wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
}