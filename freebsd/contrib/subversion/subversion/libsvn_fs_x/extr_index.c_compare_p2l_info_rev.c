#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ change_set; } ;
typedef  TYPE_2__ svn_fs_x__id_t ;
struct TYPE_8__ {TYPE_1__* entry; TYPE_2__** order; } ;
typedef  TYPE_3__ sub_item_ordered_t ;
struct TYPE_6__ {int item_count; TYPE_2__* items; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
compare_p2l_info_rev(const sub_item_ordered_t * lhs,
                     const sub_item_ordered_t * rhs)
{
  svn_fs_x__id_t *lhs_part;
  svn_fs_x__id_t *rhs_part;

  assert(lhs != rhs);
  if (lhs->entry->item_count == 0)
    return rhs->entry->item_count == 0 ? 0 : -1;
  if (rhs->entry->item_count == 0)
    return 1;

  lhs_part = lhs->order ? lhs->order[lhs->entry->item_count - 1]
                        : &lhs->entry->items[0];
  rhs_part = rhs->order ? rhs->order[rhs->entry->item_count - 1]
                        : &rhs->entry->items[0];

  if (lhs_part->change_set == rhs_part->change_set)
    return 0;

  return lhs_part->change_set < rhs_part->change_set ? -1 : 1;
}