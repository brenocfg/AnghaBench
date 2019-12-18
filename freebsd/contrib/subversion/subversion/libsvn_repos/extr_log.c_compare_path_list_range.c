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
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
struct path_list_range {TYPE_1__ range; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_path_list_range(const void *a, const void *b)
{
  struct path_list_range *plr_a = *((struct path_list_range *const *) a);
  struct path_list_range *plr_b = *((struct path_list_range *const *) b);

  if (plr_a->range.start < plr_b->range.start)
    return -1;
  if (plr_a->range.start > plr_b->range.start)
    return 1;
  if (plr_a->range.end < plr_b->range.end)
    return -1;
  if (plr_a->range.end > plr_b->range.end)
    return 1;

  return 0;
}