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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int pos_y; int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ GDashModule ;

/* Variables and functions */
 int /*<<< orphan*/  color_panel_desc ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
render_description (WINDOW * win, GDashModule * data, int *y)
{
  int w, h;

  getmaxyx (win, h, w);
  (void) h;

  draw_header (win, data->desc, " %s", (*y), 0, w, color_panel_desc);

  data->pos_y = (*y);
  (*y)++;
  (*y)++;       /* add empty line underneath description */
}