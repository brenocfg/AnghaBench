#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {int h; int w; int x; int y; int /*<<< orphan*/  win; scalar_t__ status; scalar_t__ start; scalar_t__ selectable; scalar_t__ multiple; scalar_t__ idx; scalar_t__ count; } ;
typedef  TYPE_1__ GMenu ;

/* Variables and functions */
 int /*<<< orphan*/  derwin (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xmalloc (int) ; 

GMenu *
new_gmenu (WINDOW * parent, int h, int w, int y, int x)
{
  GMenu *menu = xmalloc (sizeof (GMenu));

  memset (menu, 0, sizeof *menu);
  menu->count = 0;
  menu->idx = 0;
  menu->multiple = 0;
  menu->selectable = 0;
  menu->start = 0;
  menu->status = 0;

  menu->h = h;
  menu->w = w;
  menu->x = x;
  menu->y = y;
  menu->win = derwin (parent, menu->h, menu->w, menu->y, menu->x);

  return menu;
}