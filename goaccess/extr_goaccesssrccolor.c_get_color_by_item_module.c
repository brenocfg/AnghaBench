#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  item; int /*<<< orphan*/  module; } ;
struct TYPE_9__ {TYPE_2__* data; } ;
typedef  TYPE_1__ GSLList ;
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_2__ GColors ;
typedef  int /*<<< orphan*/  GColorItem ;

/* Variables and functions */
 int /*<<< orphan*/  color_list ; 
 int /*<<< orphan*/  find_color_item_module_in_list ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* get_color (int /*<<< orphan*/ ) ; 
 TYPE_1__* list_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* new_gcolors () ; 

GColors *
get_color_by_item_module (GColorItem item, GModule module)
{
  GColors *needle = new_gcolors (), *color = NULL;
  GSLList *match = NULL;

  needle->module = module;
  needle->item = item;

  /* find color for specific item/module pair */
  if ((match = list_find (color_list, find_color_item_module_in_list, needle)))
    color = match->data;

  /* attempt to find color by item (fallback) */
  if (!color)
    color = get_color (item);
  free (needle);

  return color;
}