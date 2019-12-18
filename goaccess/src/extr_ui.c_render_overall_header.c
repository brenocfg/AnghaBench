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
typedef  int /*<<< orphan*/  GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  color_panel_header ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_overall_header (int /*<<< orphan*/ *) ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static void
render_overall_header (WINDOW * win, GHolder * h)
{
  char *hd = get_overall_header (h);
  int col = getmaxx (stdscr);

  draw_header (win, hd, " %s", 0, 0, col, color_panel_header);
  free (hd);
}