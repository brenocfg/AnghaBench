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
struct TYPE_2__ {scalar_t__ item; scalar_t__ module; } ;
typedef  TYPE_1__ GColors ;

/* Variables and functions */

__attribute__((used)) static int
find_color_in_list (void *data, void *color)
{
  GColors *new_color = color;
  GColors *old_color = data;

  if (old_color->item != new_color->item)
    return 0;
  if (old_color->module != new_color->module)
    return 0;
  return 1;
}