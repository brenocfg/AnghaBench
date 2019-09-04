#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t idx; int size; size_t h; size_t start; TYPE_1__* items; int /*<<< orphan*/  multiple; } ;
struct TYPE_5__ {int checked; } ;
typedef  TYPE_2__ GMenu ;

/* Variables and functions */
#define  REQ_DOWN 130 
#define  REQ_SEL 129 
#define  REQ_UP 128 
 int /*<<< orphan*/  post_gmenu (TYPE_2__*) ; 

void
gmenu_driver (GMenu * menu, int c)
{
  int i;

  switch (c) {
  case REQ_DOWN:
    if (menu->idx >= menu->size - 1)
      break;
    ++menu->idx;
    if (menu->idx >= menu->h && menu->idx >= menu->start + menu->h)
      menu->start++;
    post_gmenu (menu);
    break;
  case REQ_UP:
    if (menu->idx <= 0)
      break;
    --menu->idx;
    if (menu->idx < menu->start)
      --menu->start;
    post_gmenu (menu);
    break;
  case REQ_SEL:
    if (!menu->multiple) {
      for (i = 0; i < menu->size; i++)
        menu->items[i].checked = 0;
    }
    if (menu->items[menu->idx].checked)
      menu->items[menu->idx].checked = 0;
    else
      menu->items[menu->idx].checked = 1;
    post_gmenu (menu);
    break;
  }
}