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
struct TYPE_2__ {int module; int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ GColors ;
typedef  int /*<<< orphan*/  GColorItem ;

/* Variables and functions */

__attribute__((used)) static int
find_color_item_in_list (void *data, void *needle)
{
  GColors *color = data;
  GColorItem *item = needle;

  return color->item == (GColorItem) (*(int *) item) && color->module == -1;
}