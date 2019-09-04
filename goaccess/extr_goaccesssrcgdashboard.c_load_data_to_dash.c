#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* module; } ;
struct TYPE_17__ {TYPE_10__* items; scalar_t__ sub_items_size; int /*<<< orphan*/  holder_size; } ;
struct TYPE_16__ {size_t current; scalar_t__ expanded; } ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int alloc_data; int /*<<< orphan*/  meta; int /*<<< orphan*/  holder_size; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_2__* metrics; } ;
typedef  TYPE_3__ GScroll ;
typedef  size_t GModule ;
typedef  TYPE_4__ GHolder ;
typedef  int /*<<< orphan*/  GDashData ;
typedef  TYPE_5__ GDash ;

/* Variables and functions */
 int /*<<< orphan*/  add_item_to_dash (TYPE_5__**,TYPE_10__,size_t) ; 
 int /*<<< orphan*/  add_sub_item_to_dash (TYPE_5__**,TYPE_10__,size_t,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_gdata (int) ; 

void
load_data_to_dash (GHolder * h, GDash * dash, GModule module, GScroll * gscroll)
{
  int alloc_size = 0;
  int i, j;

  alloc_size = dash->module[module].alloc_data;
  if (gscroll->expanded && module == gscroll->current)
    alloc_size += h->sub_items_size;

  dash->module[module].alloc_data = alloc_size;
  dash->module[module].data = new_gdata (alloc_size);
  dash->module[module].holder_size = h->holder_size;
  memset (&dash->module[module].meta, 0, sizeof (GDashData));

  for (i = 0, j = 0; i < alloc_size; i++) {
    if (h->items[j].metrics->data == NULL)
      continue;

    add_item_to_dash (&dash, h->items[j], module);
    if (gscroll->expanded && module == gscroll->current && h->sub_items_size)
      add_sub_item_to_dash (&dash, h->items[j], module, &i);
    j++;
  }
}