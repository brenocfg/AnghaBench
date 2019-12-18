#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ y; scalar_t__ x; } ;
struct tui_gen_win_info {scalar_t__ title; int /*<<< orphan*/  is_visible; int /*<<< orphan*/  content_in_use; int /*<<< orphan*/ * content; int /*<<< orphan*/ * handle; scalar_t__ last_visible_line; scalar_t__ content_size; scalar_t__ viewport_height; TYPE_1__ origin; scalar_t__ height; scalar_t__ width; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

void
tui_init_generic_part (struct tui_gen_win_info * win)
{
  win->width =
    win->height =
    win->origin.x =
    win->origin.y =
    win->viewport_height =
    win->content_size =
    win->last_visible_line = 0;
  win->handle = (WINDOW *) NULL;
  win->content = NULL;
  win->content_in_use =
    win->is_visible = FALSE;
  win->title = 0;
}