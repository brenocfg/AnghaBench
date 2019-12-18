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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ GSLList ;
typedef  int /*<<< orphan*/  GColors ;
typedef  int /*<<< orphan*/  GColorItem ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_NORMAL ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_list ; 
 int /*<<< orphan*/  find_color_item_in_list ; 
 TYPE_1__* list_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

GColors *
get_color (GColorItem item)
{
  GColorItem normal = COLOR_NORMAL;
  GSLList *match = NULL;

  if ((match = list_find (color_list, find_color_item_in_list, &item)))
    return (GColors *) match->data;

  if ((match = list_find (color_list, find_color_item_in_list, &normal)))
    return (GColors *) match->data;

  /* should not get here */
  FATAL ("Unable to find color item %d", item);
}